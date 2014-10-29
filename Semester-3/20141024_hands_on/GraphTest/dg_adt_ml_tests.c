/*
 * main.c
 *
 * This is the main entry point to the tests.
 * Depending on the given argument the backed test program will be invoked.
 *
 *  Created on: Oct 12, 2014
 *      Author: cchet
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "dg_adt_tests_depend.h"
#include "dg_adt_tests.h"

const int SIZE = 5;

int main(int argc, char** argv) {
	int value;

	if (argc != 2) {
		printf("Test source needs exact one integer argument");
		exit(EXIT_FAILURE);
	}
	value = atoi(argv[1]);

	switch (value) {
	case 1:
		case1_not_null_graph();
		break;
	case 2:
		case2_invalid_size_1();
		break;
	case 3:
		case3_invalid_size_2();
		break;
	case 4:
		case4_insertEdge_null_graph();
		break;
	case 5:
		case5_insertEdge_invalid_weight_1();
		break;
	case 6:
		case6_insertEdge_invalid_weight_2();
		break;
	case 7:
		case7_insertEdge_already_existing();
		break;
	case 8:
		case8_insertEdge_invalid_node_reference();
		break;
	case 9:
		case9_removeEdge_does_not_exist();
		break;
	case 10:
		case10_removeEdge_invalid_node_reference();
		break;
	case 11:
		case11_removeGraph_null();
		break;
	case 12:
		case12_printGraph_null();
		break;
	case 13:
		case13_printGraph_no_edges();
		break;
	case 14:
		case14_printGraph_reflexive();
		break;
	case 15:
		case15_printGraph_second_j();
		break;
	case 16:
		case16_createGraph();
		break;
	case 17:
		case17_insertEdge();
		break;
	case 18:
		case18_removeEdge();
		break;
	default:
		printf("Unknown test case id !!!");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

/* ############### Invalid test functions ###############*/
/* createGraph */
void case1_not_null_graph() {
	Graph* graph;

	printf("createGraph: Graph already created\n");
	graph= createTestGraph(SIZE);
	assert(createGraph(&graph, SIZE) == false);
}

void case2_invalid_size_1() {
	Graph* graph;
	graph = NULL;

	printf("createGraph: Size invalid (0)\n");
	assert(createGraph(&graph, 0) == false);
}

void case3_invalid_size_2() {
	Graph* graph;
	graph = NULL;

	printf("createGraph: Size invalid (-1)\n");
	assert(createGraph(&graph, -1) == false);
}

/* insertEdge */
void case4_insertEdge_null_graph() {
	printf("insertEdge: Insert edge on null graph\n");
	assert(insertEdge(NULL, 1, 1, 1) == false);
}

void case5_insertEdge_invalid_weight_1() {
	Graph* graph;

	printf("insertEdge: with invalid weight (0)\n");
	graph = createTestGraph(1);
	assert(insertEdge(graph, 1, 1, 0) == false);
}

void case6_insertEdge_invalid_weight_2() {
	Graph* graph;

	printf("insertEdge: with invalid weight (-1)\n");
	graph = createTestGraph(1);
	assert(insertEdge(graph, 1, 1, -1) == false);
}

void case7_insertEdge_already_existing() {
	Graph* graph;

	printf("insertEdge: Edge already existing\n");
	graph = createTestGraph(1);
	insertTestEdge(graph, 1, 1, 1);
	assert(insertEdge(graph, 1, 1, 2) == false);
}
void case8_insertEdge_invalid_node_reference() {
	Graph* graph;

	printf("insertEdge: Edge points to invalid nodes\n");
	graph = createTestGraph(1);
	assert(insertEdge(graph, 10, 10, 1) == false);
}

/* removeEdge */
void case9_removeEdge_does_not_exist() {
	Graph* graph;

	printf("removeEdge: Edge does not exists\n");
	graph = createTestGraph(1);
	assert(removeEdge(graph, 1, 1) == false);
}

void case10_removeEdge_invalid_node_reference() {
	Graph* graph;

	printf("removeEdge: Edge points to invalid nodes\n");
	graph = createTestGraph(1);
	assert(removeEdge(graph, 10, 10) == false);
}

/* removeGraph */
void case11_removeGraph_null() {
	Graph* graph;
	graph = NULL;

	printf("removeGraph: Null Graph\n");
	assert(deleteGraph(&graph) == false);
}

/* ############### Valid test functions ###############*/
/* printGraph */
void case12_printGraph_null() {
	Graph* graph;
	graph = NULL;

	printf("printGraph: Null Graph\n");
	assert(printGraph(graph) == false);
}

void case13_printGraph_no_edges() {
	Graph* graph;

	printf("printGraph: empty Graph\n");
	graph = createTestGraph(SIZE);
	assert(printGraph(graph) == true);
}

void case14_printGraph_reflexive() {
	int i;
	Graph* graph;

	printf("printGraph: reflexive Graph\n");
	graph = createTestGraph(SIZE);
	for (i = 1; i <= SIZE; ++i) {
		insertTestEdge(graph, i, i, 1);
	}

	assert(printGraph(graph) == true);
}

void case15_printGraph_second_j() {
	int i, j;
	Graph* graph;

	printf("printGraph: each second target set\n");
	graph = createTestGraph(SIZE);
	for (i = 1; i <= SIZE; ++i) {
		for (j = 1; j <= SIZE; ++j) {
			insertTestEdge(graph, i, j, 1);
			j++;
		}
	}

	assert(printGraph(graph) == true);
}
/* createGraph */
void case16_createGraph() {
	Graph* graph;

	printf("createGraph: create empty Graph\n");
	assert(createGraph(&graph, 5) == true);
	assert(printGraph(graph) == true);
}

/* insertEdge*/
void case17_insertEdge() {
	Graph* graph;
	int i, j;

	printf("createGraph: insert edge on each second target \n");
	graph = createTestGraph(SIZE);
	for (i = 1; i <= SIZE; ++i) {
		for (j = 1; j <= SIZE; ++j) {
			assert(insertEdge(graph, i, j, 1) == true);
			j++;
		}
	}
	printGraph(graph);
}

/* removeEdge */
void case18_removeEdge() {
	Graph* graph;
	int i;

	printf("createGraph: remove added edges \n");
	graph = createTestGraph(SIZE);
	for (i = 1; i <= SIZE; ++i) {
		assert(insertEdge(graph, i, i, 1) == true);
		i++;
	}
	printf("\nGraph with added edges\n");
	printGraph(graph);
	for (i = 1; i <= SIZE; ++i) {
		assert(removeEdge(graph, i, i) == true);
		i++;
	}
	printf("\nGraph with removed edges\n");
	printGraph(graph);
}

