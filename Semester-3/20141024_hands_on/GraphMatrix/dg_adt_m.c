/*
 * dg_adt_m.c
 *
 * This is the implementation of of a directed graph for handling a weighted graph
 * by usage of an Adjazenzmatrix.
 *
 *  Created on: Oct 12, 2014
 *      Author: cchet
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dg_adt_m.h"

/* ############## private visible functions ############## */
/**
 * Creates the matrix for the graph
 *
 * int n: the the x,y size of the matrix
 * return int**: the created matrix
 * failure: will exit with failure when n is not within the range 0 < n < MAX_INT
 */
static double** createMatrix(int n) {
	double** array;
	int i, j;

	/* Check for valid n */
	if (n <= 0) {
		printf("n must in range 0 < n < MAX_INT !!!\n");
		exit(EXIT_FAILURE);
	} /* if */

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

/**
 * Deletes the matrix.
 *
 * int** matrix: the matrix to be deleted
 * int n: the size of the array
 */
static void deleteMatrix(double** matrix, int n) {
	int i;

	/* Check for null matrix */
	if (matrix != NULL) {
		for (i = 0; i < n; ++i) {
			if (matrix[i] != NULL) {
				free(matrix[i]);
				matrix[i] = NULL;
			} /* if */
		} /* for */
		free(matrix);
		matrix = NULL;
	} /* if */
}

/* ############## public visible functions ############## */
bool createGraph(Graph **graph, int size) {
	double** matrix;

	/* Graph references needs to be NULL */
	if ((*graph) != NULL) {
		printf("The given graph reference must be null !!!\n");
		return false;
	} /* if */

	/* Check for valid graph size */
	if (size <= 0) {
		printf("size must in range 0 < size < MAX_INT !!! size:%d\n", size);
		return false;
	} /* if */

	*graph = malloc(sizeof(Graph));
	/* Graph creation failed */
	if (!(*graph)) {
		printf("The graph could not be created !!!\n");
		exit(EXIT_FAILURE);
	} /* if */
	matrix = createMatrix(size);

	/* Set attributes on graph */
	(*graph)->size = size;
	(*graph)->matrix = matrix;
	return true;
}

bool deleteGraph(Graph **graph) {
	/* Check for invalid pointer */
	if ((graph != NULL) || ((*graph) != NULL)) {
		return false;
	}
	/* Delete if pointer is valid */
	else {
		deleteMatrix((*graph)->matrix, (*graph)->size);
		free((*graph));
		(*graph) = NULL;
		return true;
	} /* if */
}

bool insertEdge(Graph *graph, int source, int target, double weight) {
	EdgeInfo result;

	/* Check for null graph */
	if (graph == NULL) {
		printf("Cannot insert edge in null graph !!!\n");
		return false;
	} /* if */

	/* Check for valid weight */
	if (weight <= 0) {
		printf("Weight must be in range 0 < weight < MAX_DOUBLE !!!\n");
		return false;
	} /* if */

	result = validateEdge(graph, source, target);
	switch (result) {
	case EDGE_NEW:
		graph->matrix[(source - 1)][(target - 1)] = weight;
		return true;
	case EDGE_EXISTS:
		printf(
				"Edge already exists. Remove the edge and add it afterwards !!!\n");
		return false;
	case EDGE_INVALID:
		printf("Source and target do not represent a valid edge !!!\n");
		return false;
	default:
		printf("Invalid EdgeInfo enum value detected !!!\n");
		exit(EXIT_FAILURE);
	} /* switch */
}

bool removeEdge(Graph *graph, int source, int target) {
	EdgeInfo result;

	result = validateEdge(graph, source, target);
	switch (result) {
	case EDGE_NEW:
		printf("Cannot remove not existing Edge !!!\n");
		return false;
	case EDGE_EXISTS:
		graph->matrix[(source - 1)][(target - 1)] = 0;
		return true;
	case EDGE_INVALID:
		printf("Source and target do not represent a valid edge !!!\n");
		return false;
	default:
		printf("Invalid EdgeInfo enum value detected !!!\n");
		exit(EXIT_FAILURE);
	} /* switch */
}

bool printGraph(Graph *graph) {
	int i, j;
	double** matrix;
	double value;

	/* Check for printable graph */
	if (graph == NULL) {
		printf("Graph is null and therefore cannot be printed !!!\n");
		return false;
	} /* if */
	/* Print the graph */
	else {
		/* print header line */
		printf("%4s", "");
		for (i = 1; i <= graph->size; ++i) {
			printf("%5d%5s", i, "|");
		} /* for */
		printf("\n");
		for (i = 1; i <= graph->size; ++i) {
			printf("-----------");
		} /* for */
		printf("\n");
		matrix = graph->matrix;
		for (i = 0; i < graph->size; ++i) {
			printf("%2i |", (i + 1));
			for (j = 0; j < graph->size; ++j) {
				value = matrix[i][j];
				if (value != 0) {
					printf("%3s%3.2f%3s", "", matrix[i][j], "");
				} else {
					printf("%5s%5s", "-", "");
				} /* if */
			} /* for */
			printf("\n");
		} /* for */

		return true;
	} /* if */
}

EdgeInfo validateEdge(Graph* graph, int source, int target) {
	/* Check for valid source and target */
	if ((target <= 0) || (target > graph->size) || (source <= 0)
			|| (source > graph->size)) {
		return EDGE_INVALID;
	}
	/* Check if edge already present */
	else if (graph->matrix[(source - 1)][(target - 1)] != 0) {
		return EDGE_EXISTS;
	}
	/* Else new edge */
	else {
		return EDGE_NEW;
	} /* if */
}

void visitGraph(Graph* graph, Visitor visitor) {
	int i, j;
	if (graph == NULL) {
		printf("Cannot visit NULL graph !!!\n");
		exit(EXIT_FAILURE);
	} else {
		for (i = 0; i < graph->size; ++i) {
			for (j = 0; j < graph->size; ++j) {
				if (graph->matrix[i][j] != 0) {
					visitor((i + 1), (j + 1), graph->matrix[i][j]);
				} /* if */
			} /* for */
		} /* for */
	} /* if */
}

