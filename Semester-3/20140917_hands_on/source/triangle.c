/*
 * triangle_validator.c
 *
 * This program is used to validate three given site lengths of an triangle.
 * It is validated if this triangle is an valid triangle and of which type.
 *
 * !!! Note that this program does not guarantee that site lengths with more then precision 2 are correctly handled  !!!
 * !!! This is caused by the usage of double values which are converted by "aotf" function which has rounding issues !!!
 * !!! E.g.: 2.65 will be converted to double like 2.64999999999999999998                                            !!!
 * !!! Be aware of that and use this program with just a single precisions such as 2.5                               !!!
 *
 *  Created on: Sep 18, 2014
 *      Author: cchet
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "triangle.h"

/**
 * The main function of the program
 */
int ValidateTriangle(int argc, char** argv) {

	/* Check for correct argument count */
	if (argc != 5) {
		printf("Exact 3 integer/double parameter must be given !!! count: %i",
				(argc - 2));
		return EXIT_FAILURE;
	} /* if */

	/* Validate for valid double argument */
	if (ContainsInvalidateParams(argv) == true) {
		printf(
				"The arguments are not valid integer/double !!! p1: %s | p2: %s | p3: %s",
				argv[2], argv[3], argv[4]);
		return EXIT_FAILURE;
	} /* if */

	printf(
			"Please note that the validation of a triangle could fail because of the fact\n");
	printf(
			"that double has precision failures during parsing regarding backed floating point !!!!\n");
	printf("Entered values: p1: %f | p2: %f | p3: %f\n", atof(argv[2]),
			atof(argv[3]), atof(argv[4]));

	return GetResult(
			GetTriangleType(atof(argv[2]), atof(argv[3]), atof(argv[4])));
}

bool ContainsInvalidateParams(char** argv) {
	return ((atof(argv[2]) <= 0) || (atof(argv[3]) <= 0) || (atof(argv[4]) <= 0));
}

eTriangleType GetTriangleType(double a, double b, double c) {
	if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
		return invalid;
	} else if ((a == b) && (b == c)) {
		return equilateral;
	} else if ((a == b) || (a == c) || (b == c)) {
		return isosceles;
	} else if (IsSquareTirangle(a, b, c)) {
		return square;
	} else {
		return normal;
	} /* if */
}

bool IsSquareTirangle(double a, double b, double c) {
	double coordinates[3] = { [0]=a, [1]= b, [2]= c };
	int i;
	double hypotenuse = -1;
	double adjacentSide = coordinates[0];
	double oppositeSite = -1;

	/* Determine the the hypotenuse and adjancentSide */
	for (i = 0; i < 3; ++i) {
		if (coordinates[i] <= adjacentSide) {
			adjacentSide = coordinates[i];
		}
		else if (coordinates[i] > hypotenuse) {
			hypotenuse = coordinates[i];
		} /* if */
	} /* for */

	/* Determine the oppositeSideIndex*/
	for (i = 0; i < 3; ++i) {
		if ((coordinates[i] != adjacentSide)
				&& (coordinates[i] != hypotenuse)) {
			oppositeSite = coordinates[i];
		} /* if */
	} /* for */

	/* Try to calculate the oppositeSideIndex via c^2 = root(a^2 + b^2) and compare to given length of site*/
	return ((pow(adjacentSide, 2) + pow(oppositeSite, 2)) == pow(hypotenuse, 2)) ?
			true : false;
}

int GetResult(enum eTriangleType type) {
	switch (type) {
	case invalid:
		printf(
				"our given triangle sites represent a 'invalid' triangle Please check them and try again !!!");
		return EXIT_FAILURE;
		break;
	case equilateral:
		printf("Your given triangle sites represent a 'equilateral' triangle");
		return EXIT_SUCCESS;
		break;
	case isosceles:
		printf("Your given triangle sites represent a 'isosceles' triangle");
		return EXIT_SUCCESS;
		break;
	case square:
		printf("Your given triangle sites represent a 'square' triangle");
		return EXIT_SUCCESS;
		break;
	case normal:
		printf("Your given triangle sites represent a 'normal' triangle");
		return EXIT_SUCCESS;
		break;
	default:
		printf(
				"This should not happen, because this would mean that not all enums are handled by this switch case");
		return EXIT_FAILURE;
		break;
	} /* case */

	/* Should never get here */
	printf("Switch case did not take place !!!");
	return EXIT_FAILURE;
}
