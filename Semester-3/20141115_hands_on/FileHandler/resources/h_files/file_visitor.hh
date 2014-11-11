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

#define PRINT_FILE_PROPS "print"
#define SEARCH_FILE "grep"

/**
 * This is the specification for the function which handles the
 * files visited by the calling function.
 *
 * @param
 * 		char* pathname: the fully qualified path to the visited file.
 * @param
 * 		struct stat* stat: the current file stats
 * @param
 * 		void* arg1: the generic argument which consumes any type of argument.
 * 		Be aware that this could cause problem because no type safety is supported here.
 */
typedef void (*Visitor)(char *pathname, struct stat *stat, void* arg1);
/**
 * Visits all files and directories which are children of the given path.
 *
 * @param
 * 		char* dirname: the directory to visit its content
 * @param
 * 		void* arg: the generic argument which consumes all types and must fullfill
 * 		VisitorType specified requirements.
 * @param
 * 		Visitor: the function pointer to the visitor function which handles the visited file
 */
void walkDir(char *dirname, void* arg, Visitor visitor);

/**
 * Prints all the of the file attributes.
 * Follows Visitor type function signature specification.
 *
 * @param
 * 		char* pathname: the fully qualified path to the visited file.
 * @param
 * 		char* stat: the file attributes of the visited file
 */
void print(char *pathname, struct stat *stat, void* arg1);

/**
 * Searches a text in the found ascii files.
 *
 * @param
 * 		char* filename: the current visited file name
 * @param
 * 		struct stat: the current visited file stats
 * @param
 * 		char* pattern teh pattern to be searched
 */
void grep(char *filename, struct stat *stat, char* pattern);

#endif /* FILE_HANDLER_H_ */
