/*
 * This header file contains all constants, makros and function declaration
 * the application 'weights' needs.
 *
 * weight.h
 *
 *  Created on: Sep 28, 2014
 *      Author: Thomas Herzog
 */
#include "common.h"
#include <limits.h>
#ifndef WEIGHT_H_
#define WEIGHT_H_

/* the maximum available units */
#define MAX_UNITS 8

/* The available weights of the units */
static const double UNITS[MAX_UNITS] = { 0.5, 1.25, 2.5, 5, 10, 15, 20, 25 };
/* The available counts of the units */
static const int UNIT_COUNTS[MAX_UNITS] = { 1, 1, 1, 3, 1, 1, 3, 1 };
/* The weight of the bar */
static const double BAR = 20.0;
/* Holds the solutions */
static int solutions[SHRT_MAX][MAX_UNITS];
/* The solution counter */
static int solutionCount = 0;

/**
 * Validates the given program arguments if they are valid arguments for this application.
 *
 * char** arguments: the two dimensional array of arguments
 * double* value: the parsed argument value
 * return bool: true if the arguments are valid, false otherwise
 */
bool ValidateArguments(int argc, char** arguments, double* value);

/**
 * Answers the question if the unit at the index is available to be used or not.
 *
 * usedUnitCount[MAX_UNITS]: the array holding the already used units counts on the index of the unit
 * int intendedUnitIdx: the index of the to add unit
 * return bool: true if useable, false if all counts are already used
 */
bool IsUnitAvailable(int usedUnitCount[MAX_UNITS], int intendedUnitIdx);

/**
 * Adds the unit at the index to the array and sums the unit weight to the sumWeight.
 *
 * int (*usedUnitCount)[MAX_UNITS]: the array holding the used unit count at the index of the unit
 * double* sumWeight: the summary of the weights already used
 * int idx: the index of the unit to be added
 * return void
 */
void AddUnit(int (*usedUnitCount)[MAX_UNITS], double* sumWeight, int idx);

/**
 * Removes the unit at the index to the array and subtracts the unit weight to the sumWeight.
 *
 * int (*usedUnitCount)[MAX_UNITS]: the array holding the used unit count at the index of the unit
 * double* sumWeight: the summary of the weights already used
 * int idx: the index of the unit to be added
 * return void
 */
void RemoveUnit(int (*usedUnitCount)[MAX_UNITS], double* sumWeight, int idx);

/**
 * Inits the used array by setting all counts to '0'.
 *
 * int (*usedUnitCount)[MAX_UNITS]: the array holding the used unit count at the index of the unit
 */
void Init(int (*usedUnitCount)[MAX_UNITS]);

/**
 * Prints the solutions only once. it keeps the already found solutions in a static function visible variable.
 *
 * int usedUnitCount[MAX_UNITS]: the array holding the used unit count at the index of the unit
 */
void PrintSolution(int usedUnitCount[MAX_UNITS]);

/**
 * Tries all possibilities to find combination of the units which represent the intended weight.
 *
 * int i: the current index in the array which holds the unit counts
 * int (*usedUnitCount)[MAX_UNITS]: the array holding the used unit count at the index of the unit
 * double* sumWeight: the summary of the weights
 * double* intendedWeight: the intended weight
 */
void GetUnitCombination(int i, int (*usedUnitCount)[MAX_UNITS],
		double* sumWeight, double* intendedWeight);

#endif /* WEIGHT_H_ */
