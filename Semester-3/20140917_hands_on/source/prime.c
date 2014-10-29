/*
 * prime_factorization.c
 *
 * This program is used for calculating the prime factors of an integer value.
 *
 *  Created on: Sep 18, 2014
 *      Author: cchet
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include "prime.h"

int ValidateNumber(int argc, char** argv) {
	bool primes[MAX_PRIM];
	long int calculatedPrimes[MAX_PRIM];
	int count;
	long int value;

	/* Check for invalid parameter count */
	if (argc != 3) {
		printf("Exactly one integer parameter must be given !!! count: %i \n",
				argc - 2);
		return EXIT_FAILURE;
	} /* if */

	/* Check for correct parameter type and value */
	if (((value = atoi(argv[2])) <= 1) || (value > MAX_PRIM)) {
		printf(
				"Parameter must be of type integer and must be within 2 - %i (inclusive) !!! arg: %s\n",
				MAX_PRIM, argv[2]);
		return EXIT_FAILURE;
	} /* if */

	initPrimes(primes);
	count = GetPrimeFactors(calculatedPrimes, primes, value);
	return HandleResult(calculatedPrimes, count, value);
}

int ValidateNumberErrorAware(int argc, char** argv) {
	bool primes[MAX_PRIM];
	long int calculatedPrimes[MAX_PRIM];
	int count;
	long int value;
	char *tailptr = "";
	errno = -1;

	/* Check for invalid parameter count */
	if (argc != 3) {
		printf("Exactly one integer parameter must be given !!! count: %i \n",
				argc - 2);
		return EXIT_FAILURE;
	} /* if */

	/* Check for correct parameter type and value */
	value = strtol(argv[2], &tailptr, 10);
	if (errno == ERANGE) {
		printf("Given integer overflows range (long int)");
		return EXIT_FAILURE;
	} else if (*tailptr != '\0') {
		printf("Argument is no valid integer !!! arg: %s", argv[2]);
		return EXIT_FAILURE;
	} else if ((value <= 2) || (value > MAX_PRIM)) {
		printf(
				"Argument must be of type integer and must be within 2 - %i (inclusive) !!! arg: %s\n",
				MAX_PRIM, argv[2]);
		return EXIT_FAILURE;
	} /* if */

	initPrimes(primes);
	count = GetPrimeFactors(calculatedPrimes, primes, value);
	return HandleResult(calculatedPrimes, count, value);
}

int GetPrimeFactors(long int* calculatedPrimes, bool* primes, long int value) {
	long int i;
	long int calculatedValue = 1;
	int count = 0;
	int calculatedIdx = 0;
	long int result = value;

	for (i = 2;
			(i < MAX_PRIM) && (calculatedValue < value) && (i <= result)
					&& (!primes[result]); i++) {
		if (primes[i]) {
			if ((result % i) == 0) {
				result = result / i;
				calculatedValue *= i;
				calculatedPrimes[calculatedIdx] = i;
				count++;
				calculatedIdx++;
				i--;
			} /*if*/
		} /* if */
	} /* for */

	/* Could split value into its prime factors */
	if (primes[result]) {
		calculatedPrimes[calculatedIdx] = result;
		count++;
	}
	/* prime factor split failed */
	else {
		count = -1;
	} /* if */

	return count;
}

int HandleResult(long int* calculatedPrimes, int count, long int value) {
	long int i = 0;
	long int j = 0;
	int pot = 1;

	if (count != -1) {
		printf("Prime factors of value: %li; ", value);
		while (i < count) {
			pot = 1;
			j = (i + 1);
			while ((j < count) && (calculatedPrimes[i] == calculatedPrimes[j])) {
				pot++;
				j++;
			} /* while */
			printf("%li^%i", calculatedPrimes[i], pot);
			i += pot;
			if (i < count) {
				printf(" * ");
			} else {
				printf("\n");
			} /* if */
		} /* while */
		return EXIT_SUCCESS;
	} else {
		printf("Value: %li could not be factorized\n", value);
		return EXIT_FAILURE;
	} /* if */
}

void initPrimes(bool* primes) {
	long int i, j;
	primes[0] = false;
	primes[1] = false;
	for (i = 2; i <= MAX_PRIM; i++) {
		primes[i] = true;
	} /* for */
	for (i = 2; i <= MAX_PRIM; i++) {
		if (primes[i]) {
			for (j = 2 * i; j <= MAX_PRIM; j += i) {
				primes[j] = false;
			} /* for */
		} /*if*/
	} /* for */
}

