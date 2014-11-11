/*
 * file_visitor.c
 *
 *	This is the implementation of the file_visitor. h specification.
 *
 *  Created on: Nov 1, 2014
 *      Author: cchet
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <syscall.h>
#include "file_visitor.h"
#include "common.h"

/* Specifies the buffer size for the read line of the popen(..) function */
#define MAX_BUFFER_SIZE 10
/* Avoid memory corruption when files have too long line length */
#define MAX_LINE_LENGTH 10000

/**
 * Builds the fully qualified path to the visited file.
 *
 * @param char* curPath: the current visited path
 * @param char* file: the current file within the current visited path
 * @return char*: the build fully qualified path to the file
 */
static char* buildFullyQualifiedPath(char* curPath, char* file) {
	char* path = NULL;
	bool separatorPresent = false;
	int curPathLen = strlen(curPath);

	/* check if last character is already '/' */
	if (curPath[curPathLen - 1] == '/') {
		separatorPresent = true;
	} /* if */

	path = (char*) malloc(
			(curPathLen + strlen(file))
					+ (separatorPresent ? 0 : 1) * sizeof(char));

	if (path == NULL) {
		printf("Could not allocate memory for path variable !!!");
		exit(EXIT_FAILURE);
	} /* if */

	/* Avoid characters in fresh allocated array, which happened sometimes */
	path[0] = '\0';
	strcat(path, curPath);

	if ((!separatorPresent) && (file[0] != '/')) {
		strcat(path, "/");
	} /* if */

	strcat(path, file);
	return path;
} /* buildFullyQualifiedPath */

/**
 * Checks if the current file is a ascii text file
 *
 * @param char* filename: the filename to check for ascii file
 * @retrun bool: true if the file is a ascii file false otherwise
 */
static bool isAsciiTextFile(char* filename) {
	char* prefixCommand = "file '\0";
	char* suffixCommand = "' | grep ASCII\0";
	char* fullFileCommand = (char*) malloc(
			strlen(filename) + strlen(prefixCommand) + strlen(suffixCommand)
					+ 1);
	char line[MAX_BUFFER_SIZE]; /* No need for more characters */
	bool result = false;
	FILE* commandPipe;
	/* seems that there are already characters present event after new allocation */
	fullFileCommand[0] = '\0';

	/* Allocation failed */
	if (fullFileCommand == NULL) {
		printf(
				"Could not allocate memory for system command character array !!!");
		exit(EXIT_FAILURE);
	} /* if */

	/* Build full command string */
	strcat(fullFileCommand, prefixCommand);
	strcat(fullFileCommand, filename);
	strcat(fullFileCommand, suffixCommand);

	/* open connection to command result */
	commandPipe = popen(fullFileCommand, "r");
	/* connection successful */
	if (commandPipe != NULL) {
		/* If the command returned a result the grep found the string ASCII */
		result =
				(fgets(line, MAX_BUFFER_SIZE, commandPipe) != NULL) ?
						true : false;
	} /* if */

	pclose(commandPipe);
	free(fullFileCommand);
	fullFileCommand = NULL;

	return result;
}

void walkDir(char *file, void* arg, Visitor visitor) {
	DIR* directory = NULL;
	struct stat fAttr;
	struct dirent* dirAttr = NULL;
	errno = 0;

	/* check for NULL dirName */
	if (file == NULL) {
		printf("Cannot visit NULL directory !!!");
		return;
	} /* if */

	/* get file attributes */
	if (stat(file, &fAttr) == -1) {
		printf("Error(%d) reading file attributes from file: '%s' !!!\n", errno,
				file);
		return;
	} /* if */

	/* visit file */
	visitor(file, &fAttr, arg);

	/* if directory */
	if ((S_ISDIR(fAttr.st_mode))) {
		if ((directory = opendir(file)) == NULL) {
			printf("Error reading directory: '%s'\n", file);
			return;
		} /* if */
		while ((dirAttr = readdir(directory)) != NULL) {
			if ((strcmp(dirAttr->d_name, "..") > 0)) {
				walkDir(buildFullyQualifiedPath(file, dirAttr->d_name), arg,
						visitor);
			} /* if */
		} /* while */
		closedir(directory);
	} /* if */
} /* walkDir */

/* ############## Visitor implementations ############## */
void print(char *pathname, struct stat *stat, void* arg1) {
	char* permissions;

	permissions = (char*) malloc(11 * sizeof(char));
	permissions[0] = (S_ISDIR(stat->st_mode)) ? 'd' :
						(S_ISLNK(stat->st_mode)) ? 'l' : '-';
	permissions[1] = (stat->st_mode & S_IRUSR) ? 'r' : '-';
	permissions[2] = (stat->st_mode & S_IWUSR) ? 'w' : '-';
	permissions[3] = (stat->st_mode & S_IXUSR) ? 'x' : '-';
	permissions[4] = (stat->st_mode & S_IRGRP) ? 'r' : '-';
	permissions[5] = (stat->st_mode & S_IWGRP) ? 'w' : '-';
	permissions[6] = (stat->st_mode & S_IXGRP) ? 'x' : '-';
	permissions[7] = (stat->st_mode & S_IROTH) ? 'r' : '-';
	permissions[8] = (stat->st_mode & S_IWOTH) ? 'w' : '-';
	permissions[9] = (stat->st_mode & S_IXOTH) ? 'x' : '-';
	permissions[10] = '\0';

	printf("%s %d %d %s%s\n", permissions, stat->st_uid, stat->st_gid,
			ctime(&stat->st_mtime), pathname);
} /* printFileAttrbiutes */

void grep(char *filename, struct stat *stat, char* pattern) {
	FILE* file = NULL;
	int lines = 1;
	char line[MAX_LINE_LENGTH];

	/* search only in regular files */
	if (S_ISREG(stat->st_mode) == 0) {
		return;
	} /* if */

	if (isAsciiTextFile(filename)) {

		file = fopen(filename, "r");

		if (file == NULL) {
			printf("Could not open file: '%s' !!!", filename);
			return;
		} /* if */

		while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
			if (strstr(line, pattern) != NULL) {
				printf("%s:%d: %s", filename, lines, line);
			} /* if */
			lines++;
		} /* while */

		fclose(file);
	} /* if */
}
