/*
 * prime.h
 *
 *  Created on: Sep 20, 2014
 *      Author: cchet
 */
#include "common.h"

#ifndef PRIME_H_
#define PRIME_H_

/* Defines the maximum of primes to be determined */
#define MAX_PRIM 32565

/**
 * Initializes an array of bool which index represents an prime
 * when the bool is set to true, otherwise it is not a prime.
 *
 * primeArray: the initializes bool array
 */
void initPrimes(bool*);

/**
 * Gets the prime factors of the given integer value.
 * The prime factors will be put in the given int[].
 *
 * calculatedPrimes: will contain the prime factors
 * primes: the bool[] containing the primes
 * value. the integer value to factorize
 * return count: the count of prime factors, -1 if the value could not be fully factorized.
 */
int GetPrimeFactors(long int* calculatedPrimes, bool* primes, long int value);

/**
 * Main function which gets called by the main program.
 * Checks for valid arguments and will return result
 *
 * argc: the argument count passed by the main program
 * argv: the arguments passed by the main program
 */
int ValidateNumber(int argc, char** argv);

/**
 * Same as ValidateNumber but aware of parsing errors, which atoi does not provide.
 * see: int ValidateNumber(int argc, char** argv)
 */
int ValidateNumberErrorAware(int argc, char** argv);
/**
 * Handles the result and prints the result message to the console.
 *
 * calculatedPrimes: contains the prime factors
 * count: the count of prime factors int he array
 * value: the value which got factorized.
 */
int HandleResult(long int* calculatedPrimes, int count, long int value);

#endif /* PRIME_H_ */
