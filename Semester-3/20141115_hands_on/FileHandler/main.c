/*
 * main.c
 *
 *	This source file represents the main entry to this application.
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
#include "file_visitor.h"

/**
 * Answers the question if the given directory name is a valid directory.
 *
 * @param
 * 		const char* filename: the filename to validate
 */
static bool isValidFile(const char* filename) {
	DIR* folder = NULL;
	FILE* file = NULL;
	bool result = false;
	folder = opendir(filename);
	if (folder != NULL) {
		result = true;
		closedir(folder);
	} else {
		file = fopen(filename, "r");
		if (file != NULL) {
			result = true;
			fclose(file);
		} /* if */
	} /* if */
	return result;
} /* isValidDir */

/**
 * The main entry point to this program
 *
 * @param
 * 		int argc: the argument count
 * @param
 * 		char** argv: the arguments for this program
 */
int main(int argc, char** argv) {
	char* functionName;
	char* directory;

	/* check for function argument */
	if (argc < 3) {
		printf(
				"At least the root directory and function must be given !!! E.g.: ./app.bin ./ -grep NULL");
		exit(EXIT_FAILURE);
	} /* if */

	/* Validate directory */
	if (!isValidFile((directory = argv[1]))) {
		printf("Given directory does not exist !!! dir='%s'", argv[1]);
		exit(EXIT_FAILURE);
	} /* if */

	/* Validate given function name */
	functionName = argv[2] + 1;
	if (strcmp(functionName, PRINT_FILE_PROPS) == 0) {
		traverse(directory, &print, 0, NULL);
	} else if (strcmp(functionName, SEARCH_FILE) == 0) {
		if (argc < 4) {
			printf("Missing search pattern !!!");
			exit(EXIT_FAILURE);
		} /* if */
		traverse(directory, &grep, 1, argv[3]);
	} else {
		printf("Function not supported !!! function=%s", functionName);
		exit(EXIT_FAILURE);
	} /* if */
	return EXIT_SUCCESS;
} /* main */

