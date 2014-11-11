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

/* Avoid memory corruption when files have too long line length */
#define MAX_LINE_LENGTH 10000

/**
 * Builds the fully qualified path to the visited file.
 *
 * @param
 * 		char* curPath: the current visited path
 * @param
 * 		char* file: the current file within the current visited path
 * @return
 * 		char*: the build fully qualified path to the file
 */
static char* buildFullyQualifiedPath(const char* curPath, const char* file) {
	char* path = NULL;
	bool separatorPresent = false;
	int curPathLen;

	curPathLen = strlen(curPath);

	/* Check for '/' prefix on current path */
	if (curPath[curPathLen - 1] == '/') {
		separatorPresent = true;
	} /* if */

	path = (char*) malloc(
			(curPathLen + strlen(file))
					+ (separatorPresent ? 0 : 1) * sizeof(char));

	if (path == NULL) {
		printf("Could not allocate memory for path variable !!!\n");
		exit(EXIT_FAILURE);
	} /* if */

	/* Avoid characters in fresh allocated array, which happened sometimes */
	path[0] = '\0';
	strcat(path, curPath);

	/* Check for '/' prefix on file name */
	if ((!separatorPresent) && (file[0] != '/')) {
		strcat(path, "/");
	} /* if */

	strcat(path, file);
	return path;
} /* buildFullyQualifiedPath */

/**
 * Checks if the current file is a ASCII text file
 *
 * @param
 * 		char* filename: the filename to check for ASCII file
 * @retrun
 * 		bool: true if the file is a ASCII file false otherwise
 */
static bool isAsciiTextFile(const char* filename) {
	int sysres;
	char* prefixCommand = "file '\0";
	char* suffixCommand = "' | grep ASCII > /dev/null\0";
	char* fullFileCommand;

	fullFileCommand = (char*) malloc(
			strlen(filename) + strlen(prefixCommand) + strlen(suffixCommand)
					+ 1);
	/* seems that there are already characters present event after new allocation */
	fullFileCommand[0] = '\0';

	if (fullFileCommand == NULL) {
		printf(
				"Could not allocate memory for system command character array !!!\n");
		exit(EXIT_FAILURE);
	} /* if */

	/* Build full command string */
	strcat(fullFileCommand, prefixCommand);
	strcat(fullFileCommand, filename);
	strcat(fullFileCommand, suffixCommand);

	/* perform system call */
	sysres = system(fullFileCommand);

	/* free memory */
	free(fullFileCommand);
	fullFileCommand = NULL;

	return sysres == 0 ? true : false;
} /* isAsciiTextFile */

static void walkDir(const char *file, const Visitor visitor, const int n,
		char** vargs) {
	DIR* directory = NULL;
	struct stat fAttr;
	struct dirent* dirAttr = NULL;

	/* check for NULL dirName */
	if (file == NULL) {
		printf("Cannot visit NULL directory !!!\n");
		exit(EXIT_FAILURE);
	} /* if */

	/* get file attributes */
	if (stat(file, &fAttr) == -1) {
		printf("Error(%d) reading file attributes from file: '%s' !!!\n", errno,
				file);
		return;
	} /* if */

	/* visit file */
	visitor(file, fAttr, n, vargs);

	/* if directory */
	if ((S_ISDIR(fAttr.st_mode))) {
		if ((directory = opendir(file)) == NULL) {
			printf("Error reading directory: '%s'\n", file);
			return;
		} /* if */
		while ((dirAttr = readdir(directory)) != NULL) {
			/* Exclude the UNIX directory entries '.' '..' which would lead to stack overflow */
			if ((strcmp(dirAttr->d_name, "..") > 0)) {
				walkDir(buildFullyQualifiedPath(file, dirAttr->d_name), visitor,
						n, vargs);
			} /* if */
		} /* while */
		closedir(directory);
	} /* if */
} /* walkDir */

void traverse(const char *dirname, const Visitor visitor, const int n, ...) {
	va_list vargs;
	char** args = NULL;
	char* temp = NULL;
	int i;
	int j, argSize;
	va_start(vargs, n);

	if (n > 0) {
		i = 0;
		args = (char**) malloc(n * sizeof(char**));
		if (args == NULL) {
			printf("Could not allocate memory for arg array !!!\n");
			exit(EXIT_FAILURE);
		} /* if */
		/* copy vargs to array so that t can be passed through the recursive calls. */
		while (i < n) {
			temp = va_arg(vargs, char*);
			argSize = sizeof(temp);
			args[i] = malloc(sizeof(temp));
			for (j = 0; j < argSize; ++j) {
				args[i][j] = temp[j];
			} /* for */
			i++;
		} /* while */
	} /* if */
	walkDir(dirname, visitor, n, args);

	if (n > 0) {
		for (i = 0; i < n; ++i) {
			free(args[i]);
		}
		free(args);
	}
} /* traverse */

/* ############## Visitor implementations ############## */
void print(const char *pathname, const struct stat stat, const int n,
		char** array) {
	char* permissions;

	permissions = (char*) malloc(11 * sizeof(char));
	if (permissions == NULL) {
		printf("Could not allocate memory for permission string !!!\n");
		exit(EXIT_FAILURE);
	} /* if */

	/* build permission string with bitmask to file properties */
	permissions[0] = (S_ISDIR(stat.st_mode)) ? 'd' :
						(S_ISLNK(stat.st_mode)) ? 'l' : '-';
	permissions[1] = (stat.st_mode & S_IRUSR) ? 'r' : '-';
	permissions[2] = (stat.st_mode & S_IWUSR) ? 'w' : '-';
	permissions[3] = (stat.st_mode & S_IXUSR) ? 'x' : '-';
	permissions[4] = (stat.st_mode & S_IRGRP) ? 'r' : '-';
	permissions[5] = (stat.st_mode & S_IWGRP) ? 'w' : '-';
	permissions[6] = (stat.st_mode & S_IXGRP) ? 'x' : '-';
	permissions[7] = (stat.st_mode & S_IROTH) ? 'r' : '-';
	permissions[8] = (stat.st_mode & S_IWOTH) ? 'w' : '-';
	permissions[9] = (stat.st_mode & S_IXOTH) ? 'x' : '-';
	permissions[10] = '\0';

	/* print the unix like file entry */
	printf("%s %d %d %s%s\n", permissions, stat.st_uid, stat.st_gid,
			ctime(&stat.st_mtime), pathname);

	free(permissions);
} /* print */

void grep(const char *filename, const struct stat stat, const int n,
		char** array) {
	FILE* file = NULL;
	int lines = 1;
	char line[MAX_LINE_LENGTH];
	char* pattern;

	/* search only in regular files */
	if (S_ISREG(stat.st_mode) == 0) {
		return;
	} /* if */

	/* Only search on ASCII files */
	if (isAsciiTextFile(filename)) {

		/* get argument */
		if (n > 0) {
			pattern = array[0];
		} else {
			pattern = "";
		} /* if */

		file = fopen(filename, "r");

		if (file == NULL) {
			printf("Could not open file: '%s' !!!\n", filename);
			return; /* no need to break program */
		} /* if */

		while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
			if (strstr(line, pattern) != NULL) {
				printf("%s:%d: %s", filename, lines, line);
			} /* if */
			lines++;
		} /* while */

		fclose(file);
	} /* if */
} /* grep */
