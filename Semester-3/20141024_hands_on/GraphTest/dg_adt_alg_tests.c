/*
 * dg_adt_alg_tests.c
 *
 *	This source tests the source dg_adt_alg.c and does not depend on the concrete
 *	implementation of dg_adt.h.
 *	Therefore that the function names are self speaking no further documentation will
 *	be provided.
 *
 *  Created on: Oct 19, 2014
 *      Author: cchet
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dg_adt_alg_tests.h"
#include "dg_adt_tests_depend.h"
#include "dg_adt_alg.h"
#include "dg_adt.h"

static const int SIZE = 5;

int main(int argc, char** argv) {
	int value;
	if (argc != 2) {
		printf("Exactly one argument must be given !!! argc=%d !!!\n", argc);
		exit(EXIT_FAILURE);
	}
	value = atoi(argv[1]);
	switch (value) {
	case 1:
		case1_initContext_null_graph();
		break;
	case 2:
		case2_initContext_invalid_size1();
		break;
	case 3:
		case3_initContext_invalid_size2();
		break;
	case 4:
		case4_initContext_existing_context();
		break;
	case 5:
		case5_initContext_graph_not_in_conjunction();
		break;
	case 6:
		case6_destroyContext_non_existing_context();
		break;
	case 7:
		case7_isReflexive_no_context();
		break;
	case 8:
		case8_isSymetric_no_context();
		break;
	case 9:
		case9_isAsymetric_no_context();
		break;
	case 10:
		case10_isTransitiv_no_context();
		break;
	case 11:
		case11_invertGraph_null_graph();
		break;
	case 12:
		case12_invertGraph_existing_context();
		break;
	case 13:
		case13_invertGraph_invalid_size1();
		break;
	case 14:
		case14_invertGraph_invalid_size2();
		break;
	case 15:
		case15_invertGraph_invalid_size3();
		break;
	case 16:
		case16_printGraphProperties_null_graph();
		break;
	case 17:
		case17_initContext_destroyContext();
		break;
	case 18:
		case18_isReflexive_true();
		break;
	case 19:
		case19_isSymetric_true();
		break;
	case 20:
		case20_isAsymetric_true();
		break;
	case 21:
		case21_isTransitive_true();
		break;
	case 22:
		case22_isReflexive_false();
		break;
	case 23:
		case23_isSymetric_false();
		break;
	case 24:
		case24_isAsymetric_false();
		break;
	case 25:
		case25_isTransitive_false();
		break;
	case 26:
		case26_invertGraph();
		break;
	case 27:
		case27_printGraphProperties();
		break;
	default:
		printf("Unknown test case !!! case=%d", value);
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

/* Context control  */
void case1_initContext_null_graph() {
	printf("Case 1: initContext on NULL graph\n");
	assert(initContext(NULL, SIZE) == false);
}

void case2_initContext_invalid_size1() {
	Graph* graph;
	printf("Case 2: initContext invalid size(0)\n");
	graph = createTestGraph(SIZE);
	assert(initContext(graph, 0) == false);
}

void case3_initContext_invalid_size2() {
	Graph* graph;
	printf("Case 3: initContext invalid size(-1)\n");
	graph = createTestGraph(SIZE);
	assert(initContext(graph, -1) == false);
}

void case4_initContext_existing_context() {
	Graph* graph;
	printf("Case 4: initContext on existing context\n");
	graph = createTestGraph(SIZE);
	assert(initContext(graph, SIZE) == true);
	assert(initContext(graph, SIZE) == false);
}
void case5_initContext_graph_not_in_conjunction() {
	Graph* graph;
	printf("Case 5: graph not in conjunction with initialized context\n");
	graph = createTestGraph(SIZE);
	initContext(graph, SIZE - 1);
}

void case6_destroyContext_non_existing_context() {
	printf("Case 6: destroyContext on not existing context\n");
	assert(destroyContext() == false);
}

/* isReflexive */
void case7_isReflexive_no_context() {
	printf("Case 7: isReflexive on not existing context\n");
	assert(isReflexive() == EXIT_FAILURE);
}

/* isSymetric */
void case8_isSymetric_no_context() {
	printf("Case 8: isSymetric on not existing context\n");
	assert(isSymmetric() == EXIT_FAILURE);
}

/* isAsymetric */
void case9_isAsymetric_no_context() {
	printf("Case 9: isAsymetric on not existing context\n");
	assert(isAsymmetric() == EXIT_FAILURE);
}

/* isTransitiv */
void case10_isTransitiv_no_context() {
	printf("Case 10: isTransitiv on not existing context\n");
	assert(isTransitive() == EXIT_FAILURE);
}

void case11_invertGraph_null_graph() {
	printf("Case 11: invertGraph on null graph\n");
	assert(invert(NULL, SIZE) == false);
}

void case12_invertGraph_existing_context() {
	Graph* graph;
	printf("Case 12: invertGraph on existing context\n");
	graph = createTestGraph(SIZE);
	initContext(graph, SIZE);
	assert(invert(graph, SIZE) == false);
}

void case13_invertGraph_invalid_size1() {
	Graph* graph;
	printf("Case 13: invertGraph invalid size(0)\n");
	graph = createTestGraph(SIZE);
	assert(invert(graph, 0) == false);
}

void case14_invertGraph_invalid_size2() {
	Graph* graph;
	printf("Case 14: invertGraph invalid size(-1)\n");
	graph = createTestGraph(SIZE);
	assert(invert(graph, -1) == false);
}

void case15_invertGraph_invalid_size3() {
	Graph* graph;
	printf("Case 14: invertGraph size not in conjunction with graph size\n");
	graph = createTestGraph(SIZE);
	invert(graph, SIZE - 1);
}

void case16_printGraphProperties_null_graph() {
	printf("Case 14: printGraphProperties on null graph\n");
	assert(printGraphProperties(NULL) == false);
}

/* ############## Valid tests ############## */
void case17_initContext_destroyContext() {
	Graph* graph;
	printf("Case 17: init- and destroyContext\n");
	graph = createTestGraph(SIZE);
	assert(initContext(graph, SIZE) == true);
	assert(destroyContext() == true);
	assert(initContext(graph, SIZE) == true);
	assert(destroyContext() == true);
}

void case18_isReflexive_true() {
	Graph* graph;
	printf("Case 18: isReflexive (true)\n");
	graph = createTestGraph(SIZE);

	insertTestEdge(graph, 1, 1, 1);
	insertTestEdge(graph, 2, 2, 1);
	insertTestEdge(graph, 3, 3, 1);
	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 3, 1);
	insertTestEdge(graph, 1, 3, 1);

	assert(printGraph(graph) == true);

	assert(initContext(graph, SIZE) == true);
	assert(isReflexive() == true);
	assert(destroyContext() == true);
}

void case19_isSymetric_true() {
	Graph* graph;
	printf("Case 19: isSymetric (true)\n");
	graph = createTestGraph(SIZE);

	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 1, 1);
	insertTestEdge(graph, 2, 3, 1);
	insertTestEdge(graph, 3, 2, 1);
	insertTestEdge(graph, 1, 3, 1);
	insertTestEdge(graph, 3, 1, 1);

	assert(printGraph(graph) == true);

	assert(initContext(graph, SIZE) == true);
	assert(isSymmetric() == true);
	assert(destroyContext() == true);
}

void case20_isAsymetric_true() {
	Graph* graph;
	printf("Case 20: isAsymetric (true)\n");
	graph = createTestGraph(SIZE);

	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 3, 1);
	insertTestEdge(graph, 3, 4, 1);
	insertTestEdge(graph, 1, 3, 1);
	insertTestEdge(graph, 2, 4, 1);
	insertTestEdge(graph, 1, 4, 1);

	assert(printGraph(graph) == true);

	assert(initContext(graph, SIZE) == true);
	assert(isAsymmetric() == true);
	assert(destroyContext() == true);

}

void case21_isTransitive_true() {
	Graph* graph;
	printf("Case 21: isTransitive (true)\n");
	graph = createTestGraph(SIZE);

	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 3, 1);
	insertTestEdge(graph, 1, 3, 1);
	insertTestEdge(graph, 3, 4, 1);
	insertTestEdge(graph, 1, 4, 1);
	insertTestEdge(graph, 2, 4, 1);

	assert(printGraph(graph) == true);

	assert(initContext(graph, SIZE) == true);
	assert(isTransitive() == true);
	assert(destroyContext() == true);
}

void case22_isReflexive_false() {
	Graph* graph;
	printf("Case 22: isReflexive (false)\n");
	graph = createTestGraph(SIZE);

	insertTestEdge(graph, 1, 1, 1);
	insertTestEdge(graph, 2, 2, 1);
	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 3, 1);

	assert(printGraph(graph) == true);

	assert(initContext(graph, SIZE) == true);
	assert(isReflexive() == false);
	assert(destroyContext() == true);
}

void case23_isSymetric_false() {
	Graph* graph;
	printf("Case 23: isSymetric (false)\n");
	graph = createTestGraph(SIZE);

	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 1, 1);
	insertTestEdge(graph, 2, 3, 1);
	insertTestEdge(graph, 3, 2, 1);
	insertTestEdge(graph, 1, 3, 1);

	assert(printGraph(graph) == true);

	assert(initContext(graph, SIZE) == true);
	assert(isSymmetric() == false);
	assert(destroyContext() == true);
}

void case24_isAsymetric_false() {
	Graph* graph;
	printf("Case 24: isAsymetric (false)\n");
	graph = createTestGraph(SIZE);

	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 1, 1);
	insertTestEdge(graph, 2, 3, 1);
	insertTestEdge(graph, 3, 2, 1);
	insertTestEdge(graph, 1, 3, 1);
	insertTestEdge(graph, 3, 1, 1);

	assert(printGraph(graph) == true);

	assert(initContext(graph, SIZE) == true);
	assert(isAsymmetric() == false);
	assert(destroyContext() == true);
}

void case25_isTransitive_false() {
	Graph* graph;
	printf("Case 25: isTransitive (false)\n");
	graph = createTestGraph(SIZE);

	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 3, 1);
	insertTestEdge(graph, 3, 4, 1);
	insertTestEdge(graph, 2, 4, 1);

	assert(printGraph(graph) == true);

	assert(initContext(graph, SIZE) == true);
	assert(isTransitive() == false);
	assert(destroyContext() == true);
}

void case26_invertGraph() {
	Graph* graph;
	Graph* new;
	printf("Case 26: invertGraph\n");

	graph = createTestGraph(SIZE);
	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 1, 2);
	insertTestEdge(graph, 2, 3, 3);
	insertTestEdge(graph, 3, 2, 4);
	insertTestEdge(graph, 1, 3, 5);
	printGraph(graph);

	new = invert(graph, SIZE);
	printGraph(new);
}

void case27_printGraphProperties() {
	Graph* graph;
	printf("Case 26: printGraphProperties\n");

	graph = createTestGraph(SIZE);
	insertTestEdge(graph, 1, 2, 1);
	insertTestEdge(graph, 2, 1, 2);
	insertTestEdge(graph, 2, 3, 3);
	insertTestEdge(graph, 3, 2, 4);
	insertTestEdge(graph, 1, 3, 5);
	printGraph(graph);
	printGraphProperties(graph);
}
