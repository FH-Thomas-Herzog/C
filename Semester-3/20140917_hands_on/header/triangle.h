/*
 * triangle.h
 *
 *	This header files specifies the types and functions used by the triangle sub-program.
 *
 *  Created on: Sep 20, 2014
 *      Author: cchet
 */

/* User libs */
#include "common.h"

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

/*
 * Specifies the types which the given triangle can be of
 */
typedef enum eTriangleType {
	equilateral, isosceles, square, normal, invalid
} eTriangleType;

/**
 * This function represents the main entry point in this sub program, called by the main program.
 * Please note that triangles defined by double side lengths are not guaranteed to be detected correctly,
 * because of the fact that there could occur precision errors.
 * This is an restriction of this program.
 *
 * int argc: the argument count
 * char* argv: the given arguments
 */
int ValidateTriangle(int argc, char** argv);

/**
 * Validates the given arguments if they represent a valid double value.
 * The function 'atof' is used which returns 0 when an invalid parameter has been found.
 * This can be used here because a 0 side length is not allowed for valid triangles.
 *
 * argv: the pointer to the arguments array
 *
 * return: true if all arguments are valid doubles in the correct range
 */
bool ContainsInvalidateParams(char** argv);

/*
 * Gets the triangle type which is defined in the enumeration type "eTriangleType".
 *
 * double a: the a side of the triangle
 * double b: the b side of the triangle
 * double c: the c side of the triangle
 *
 * return eTriangleType: the triangle type
 *
 * see: typedef enum eTriangleType {...}
 */
eTriangleType GetTriangleType(double a, double b, double c);

/**
 * Answers the question if the given triangle side lengths representing a square triangle.
 *
 * double a: the a side of the triangle
 * double b: the b side of the triangle
 * double c: the c side of the triangle
 *
 * return bool: true if the triangle is a square triangle
 */
bool IsSquareTirangle(double a, double b, double c);

/**
 * Analyzes the determined triangle type and returns the proper return value
 * and prints a message to the console.
 *
 * eTriangleType type: the determined triangle type.
 * return int: 0-if valid triangle, 1-if not
 */
int GetResult(enum eTriangleType type);

#endif /* TRIANGLE_H_ */
