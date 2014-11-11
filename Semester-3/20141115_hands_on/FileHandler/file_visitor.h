/*
 * file_handler.h
 *
 *	This header file specifies the functions for the handling of files.
 *
 *  Created on: Nov 1, 2014
 *      Author: cchet
 */

#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <stdarg.h>

/* For comparison of the intended function */
#define PRINT_FILE_PROPS "print"
#define SEARCH_FILE "grep"

/**
 * This is the specification for the function which handles the
 * files visited by the calling function.
 *
 * @param
 * 		const char* pathname: the fully qualified path to the visited file.
 * @param
 * 		const struct stat stat: the current file stats
 * @param
 * 		const n the count of the arguments in the array
 * @param
 * 		array the arguments array
 */
typedef void (*Visitor)(const char *pathname, const struct stat stat, const int n, char** array);

/**
 * Visits all files and directories which are children of the given path.
 *
 * @param
 * 		const char* dirname: the directory to visit its content
 * @param
 * 		const Visitor: the function pointer to the visitor function which handles the visited file
 * @param
 * 		const n: the count of vargs arguments
 * @param
 * 		The varargs for the visitor function
 */
void traverse(const char *dirname, const Visitor visitor, const int n, ...);

/**
 * Prints all the of the file attributes.
 * Follows Visitor type function signature specification.
 *
 * @param
 * 		const char* pathname: the fully qualified path to the visited file.
 * @param
 * 		const struct stat stat: the current file stats
 * @param
 * 		const n the count of the arguments in the array
 * @param
 * 		array the arguments array
 */
void print(const char *pathname, const struct stat stat, const int n, char** array);

/**
 * Searches a text in the found ascii files.
 *
 * @param
 * 		const char* filename: the current visited file name
 * @param
 * 		const struct stat stat: the current file stats
 * @param
 * 		const n the count of the arguments in the array
 * @param
 * 		array the arguments array
 */
void grep(const char *filename, const struct stat stat, const int n, char** array);

#endif /* FILE_HANDLER_H_ */
