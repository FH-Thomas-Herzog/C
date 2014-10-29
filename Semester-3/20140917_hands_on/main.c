/*
 * main.c
 *
 * This represents the source of the main program which delegates to the sub program
 * depending on the given application type.
 *
 *  Created on: Sep 18, 2014
 *      Author: cchet
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "triangle.h"
#include "prime.h"

int main(int argc, char** argv) {
	int application_type;
	if (argc < 2) {
		printf("No arguments are given !!!\n");
		printf("./main.h <application_type> <application_parameters>\n");
		return EXIT_FAILURE;
	} else {
		application_type = atoi(argv[1]);
		/* Triangle validator */
		if (application_type == triangle) {
			return ValidateTriangle(argc, argv);
		}
		/* prime factorizer */
		else if (application_type == prime) {
			return ValidateNumber(argc, argv);
		}
		/* prime factorizer error aware */
		else if (application_type == prime_errno) {
			return ValidateNumberErrorAware(argc, argv);
		}
		/* unknown application type */
		else {
			printf("Application type is unknown !!! application_type: %s\n",
					argv[1]);
			return EXIT_FAILURE;
		} /* if */
	} /* if */
}

