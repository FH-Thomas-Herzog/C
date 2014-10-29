/*
 * dg_adt_test_m.c
 *
 * This source file implements the test depended functions.
 *
 *  Created on: Oct 12, 2014
 *      Author: cchet
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dg_adt_tests_depend.h"
#include "dg_adt_m.h"

/**
 * Creates the by graph backed matrix.
 *
 * int n: the size of the first and second dimension of the matrix.
 */
static double** createTestMatrix(int n) {
	double** array;
	int i, j;

	array = malloc(n * sizeof(double *));
	for (i = 0; i < n; i++) {
		array[i] = malloc(n * sizeof(double));
	} /* for */

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			array[i][j] = 0;
		} /* for */
	} /* for */

	return array;
}

Graph* createTestGraph(int size) {
	Graph* graph = malloc(sizeof(Graph));

	/* Set attributes on graph */
	graph->size = size;
	graph->matrix = createTestMatrix(size);
	return graph;
}

void insertTestEdge(Graph* graph, int source, int target, double weight) {
	graph->matrix[(source - 1)][(target - 1)] = weight;
}

