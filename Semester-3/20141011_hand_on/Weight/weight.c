/*
 * This program detects the unit combination for a certain weight.
 * All of the solutions will be detected and print to the console.
 * weight.c
 *
 *  Created on: Sep 28, 2014
 *      Author: Thomas Herzog
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weight.h"

int main(int argc, char** argv) {
	int usedUnitCount[MAX_UNITS];
	int i;
	double sumWeight;
	double value;

	/* Exit if arguments are invalid */
	if (!ValidateArguments(argc, argv, &value)) {
		return EXIT_FAILURE;
	} /* if */

	/* calculate unit combination */
	i = 0;
	sumWeight = 0;
	value -= BAR;
	Init(&usedUnitCount);
	GetUnitCombination(i, &usedUnitCount, &sumWeight, &value);

	if (solutionCount == 0) {
		printf(
				"Sorry no unit combination found for your intended weight found !!!");
	} /* if */
	return EXIT_SUCCESS;
}

void Init(int (*usedUnitCount)[MAX_UNITS]) {
	int i;
	for (i = 0; i < MAX_UNITS; ++i) {
		(*usedUnitCount)[i] = 0;
	} /* for */
}

void PrintSolution(int usedUnitCount[MAX_UNITS]) {
	int i, j;
	bool alreadyFound = false;

	/* Find out if solution already found over all found solutions */
	i = 0;
	while ((i < solutionCount) && (!alreadyFound)) {
		j = 0;
		alreadyFound = true;
		/* If solution not at index i then break search */
		while ((j < MAX_UNITS) && (alreadyFound)) {
			if (solutions[i][j] != usedUnitCount[j]) {
				alreadyFound = false;
			} /* if */
			j++;
		} /* while */
		i++;
	} /* while */

	/* If not already found add the newly found solution */
	if (!alreadyFound) {
		solutionCount += 1;
		printf("--------------\n");
		printf("Solution %d:\n", solutionCount);
		printf("--------------\n");
		for (i = 0; i < MAX_UNITS; ++i) {
			solutions[(solutionCount - 1)][i] = usedUnitCount[i];
			if (usedUnitCount[i] != 0) {
				printf("unit %d | weight: %6.2f | count: %d pair\n", i,
						UNITS[i], usedUnitCount[i]);
			} /* if */
		} /* for */
		printf("\n");
	} /* if */
}

void GetUnitCombination(int i, int (*usedUnitCount)[MAX_UNITS],
		double* sumWeight, double* intendedWeight) {
	int j, k, m;
	/* Iterate over all remaining units */
	for (j = i; j < MAX_UNITS; ++j) {
		/* Check if at least one unit count is left */
		if (IsUnitAvailable(*usedUnitCount, j)) {
			/* Iterate over the remaining unit UNIT_COUNTS */
			for (k = (*usedUnitCount)[j]; k < UNIT_COUNTS[j]; k++) {
				/* Add the unit count */
				AddUnit(usedUnitCount, sumWeight, j);
				/* If summary fits intended solution found */
				if (*sumWeight == *intendedWeight) {
					PrintSolution(*usedUnitCount);
				}
				/* To large need to go back on unit count */
				else if (*sumWeight > *intendedWeight) {
					RemoveUnit(usedUnitCount, sumWeight, j);
				}
				/* Otherwise keep trying */
				else {
					GetUnitCombination((i + 1), usedUnitCount, sumWeight,
							intendedWeight);
				} /* if */

			} /* for */
			/* Remove added units */
			for (m = 0; m < (*usedUnitCount)[j]; ++m) {
				RemoveUnit(usedUnitCount, sumWeight, j);
			} /* for */
		} /* if */
	} /* for */
}

void AddUnit(int (*usedUnitCount)[MAX_UNITS], double* sumWeight, int idx) {
	/* Increase count and weight of used unit */
	if ((*usedUnitCount)[idx] < UNIT_COUNTS[idx]) {
		*sumWeight += (UNITS[idx] * 2);
		(*usedUnitCount)[idx] += 1;
	}
}

void RemoveUnit(int (*usedUnitCount)[MAX_UNITS], double* sumWeight, int idx) {
	/* Decrease unit count and weight of removed unit */
	if ((*usedUnitCount)[idx] > 0) {
		*sumWeight -= (UNITS[idx] * 2);
		(*usedUnitCount)[idx] -= 1;
	} /* if */
}

bool IsUnitAvailable(int usedUnitCount[MAX_UNITS], int idx) {
	return (UNIT_COUNTS[idx] > usedUnitCount[idx]) ? true : false;
}

bool ValidateArguments(int argc, char** argv, double* value) {
	char* tail = "";
	int i = 0;
	double maxValue = 0;

	/* Handle invalid argument count */
	if (argc != 2) {
		printf(
				"Program accepts exactly one argument of type double !!! argc: %d",
				(argc - 1));
		return false;
	} /* if */

	/* Check if argument is valid double argument */
	*value = strtod(argv[1], &tail);
	if (strlen(tail) != 0) {
		printf("Argument is no valid double !!! argument: %s", argv[1]);
		return false;
	} /* if */

	/* Check if argument is in valid range */
	for (i = 0; i < MAX_UNITS; ++i) {
		maxValue += (UNITS[i] * (UNIT_COUNTS[i] * 2));
	} /* for */

	/* Value violates range */
	if ((*value < BAR) || (*value > maxValue)) {
		printf(
				"Requested weight is not available !!! BAR: %3.2f | max-unit-weight: %3.2f | requested: %3.2f",
				BAR, maxValue, *value);
		return false;
	}
	/* weight equals used BAR */
	else if (*value == BAR) {
		printf(
				"Requested weight equals BAR weight, so need to add any units\n");
		return false;
	} /* if */

	/* everything is ok */
	return true;
}
