/*
 * graph_algs.c
 *
 *	This source performs validations on a graph and is context depended.
 *	This this means a context must be initialized for some functions
 *	This to function properly.
 *	This The context will copy the graph into a matrix on which the
 *	the validations will be performed.
 *
 *  Created on: Oct 13, 2014
 *      Author: cchet
 */
#include <stdlib.h>
#include <stdio.h>
#include "dg_adt_alg.h"

/* ############## private global members ############## */
static double** matrix = NULL;
static int size = 0;
static bool contextActive = false;

/* ############## private sued functions ############## */
/**
 * Validates the context and handles it depending on the given flags.
 *
 * bool active: true if the context must be active
 * bool strict: true if the program shall exist
 * return bool: true if the context is active, false otherwise,
 * but depends on strict flag which will exit program with an failure
 */
static bool validateContext(bool active, bool strict) {
	bool valid = true;
	if (active) {
		if (!contextActive) {
			printf("Context not active !!!\n");
			valid = false;
		} /* if */
	} else {
		if (contextActive) {
			printf("Context already active !!!\n");
			valid = false;
		} /* if */
	} /* if */
	if ((!valid) && (strict)) {
		exit(EXIT_FAILURE);
	} /* if */
	return valid;
}

/**
 * Creates the matrix which holds the context depended graph.
 */
static void createAlgMatrix() {
	int i, j;

	validateContext(true, true);

	matrix = malloc(size * sizeof(double *));
	for (i = 0; i < size; i++) {
		matrix[i] = malloc(size * sizeof(double));
	} /* for */

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			matrix[i][j] = 0;
		} /* for */
	} /* for */
}

/**
 * Deletes the matrix which held the context depended graph
 */
static void deleteAlgMatrix() {
	int i;

	validateContext(true, true);

	if (matrix != NULL) {
		for (i = 0; i < size; ++i) {
			if (matrix[i] != NULL) {
				free(matrix[i]);
				matrix[i] = NULL;
			} /* if */
		} /* for */
		free(matrix);
		matrix = NULL;
	} /* if */
}

/**
 * Copies the graph nodes into the backed matrix
 *
 * int source: the source node id
 * int target: the target node id
 * double: the weight of the edge which connects the nodes
 */
static void visit(int source, int target, double weight) {
	validateContext(true, true);
	if ((source > size) || (target > size) || (size < source)
			|| (size < target)) {
		printf(
				"Visited graph not in conjunction with initialized context !!!\n");
		exit(EXIT_FAILURE);
	} /* if */
	matrix[(source - 1)][(target - 1)] = weight;
}

/**
 * Prints the graph nodes if the connecting edge has an weight > 0
 *
 * int source: the source node id
 * int target: the target node id
 * double: the weight of the edge which connects the nodes
 */
static void print(int source, int target, double weight) {
	if (weight != 0) {
		printf("source=%d -> target=%d (%3.2f)\n", source, target, weight);
	} /* if */
}

/* ############## public sued functions ############## */
bool initContext(Graph* graph, int n) {
	if (!validateContext(false, false)) {
		return false;
	} else if (n <= 0) {
		printf("Invalid size for graph !!!\n");
		return false;
	} else if (graph == NULL) {
		printf("Cannot initialize context on null graph !!!\n");
		return false;
	} /* if */
	size = n;
	contextActive = true;
	createAlgMatrix();
	visitGraph(graph, &visit);
	return true;
}

bool destroyContext() {
	if (!validateContext(true, false)) {
		return false;
	} /* if */
	deleteAlgMatrix();
	contextActive = false;
	size = 0;
	return true;
}

bool isReflexive() {
	int i, j;
	bool fail = false;

	validateContext(true, true);

	i = 0;
	while ((i < size) && (!fail)) {
		j = 0;
		while ((j < size) && (!fail)) {
			if (matrix[i][j] != 0) {
				fail = (matrix[i][i] == 0) || (matrix[j][j] == 0);
			} /* if */
			j++;
		} /* while */
		i++;
	} /* while */

	return !fail;
}

bool isSymmetric() {
	bool fail = false;
	int i, j;

	validateContext(true, true);

	i = 0;
	while ((i < size) && (!fail)) {
		j = 0;
		while ((j < size) && (!fail)) {
			if (matrix[i][j] != 0) {
				fail = matrix[j][i] == 0;
			} /* if */
			j++;
		} /* while */
		i++;
	} /* while */

	return !fail;
}

bool isAsymmetric() {
	validateContext(true, true);

	return !isSymmetric() && !isReflexive();
}

bool isTransitive() {
	bool fail = false;
	int i, j, k;

	validateContext(true, true);

	k = 0;
	while ((k < size) && (!fail)) {
		i = 0;
		while ((i < size) && (!fail)) {
			if (matrix[k][i] != 0) {
				j = 0;
				while ((j < size) && (!fail)) {
					if ((matrix[i][j]) != 0) {
						fail = (matrix[k][j] == 0);
					} /* if */
					j++;
				} /* while */
			} /* if */
			i++;
		} /* while */
		k++;
	} /* while */

	return !fail;

}

Graph* invert(Graph* graph, int n) {
	Graph* nGraph = NULL;
	int i, j;

	validateContext(false, true);

	/* prepare context */
	initContext(graph, n);

	/* create graph */
	createGraph(&nGraph, size);

	/* copy inverted */
	i = j = 0;
	while (i < n) {
		j = i + 1;
		while (j < n) {
			if (matrix[j][i] != 0) {
				insertEdge(nGraph, (i + 1), (j + 1), matrix[j][i]);
			} /* if */
			if (matrix[i][j] != 0) {
				insertEdge(nGraph, (j + 1), (i + 1), matrix[i][j]);
			} /* if */
			j++;
		} /* while */
		i++;
	} /* while */

	/* destroy context */
	destroyContext();

	return nGraph;
}

bool printGraphProperties(Graph* graph) {
	if (graph == NULL) {
		printf("Cannot print graph properties of null graph !!!\n");
		return false;
	} /* if */
	visitGraph(graph, &print);
	return true;
}

