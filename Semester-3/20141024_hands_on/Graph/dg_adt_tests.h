/*
 * graph_tests.h
 *
 *	This header files specifies the tests functions to be implemented and
 *	used for each implementation of dg_adt.h
 *	Therefore that the functions have a self speaking name, no comments needed
 *
 *  Created on: Oct 17, 2014
 *      Author: cchet
 */

#ifndef GRAPH_TESTS_H_
#define GRAPH_TESTS_H_

#include "dg_adt.h"

/* ############### Invalid test functions ###############*/
/* createGraph */
void case1_not_null_graph();

void case2_invalid_size_1();

void case3_invalid_size_2();

/* insertEdge */
void case4_insertEdge_null_graph();

void case5_insertEdge_invalid_weight_1();

void case6_insertEdge_invalid_weight_2();

void case7_insertEdge_already_existing();

void case8_insertEdge_invalid_node_reference();

/* removeEdge */
void case9_removeEdge_does_not_exist();

void case10_removeEdge_invalid_node_reference();

/* removeGraph */
void case11_removeGraph_null();

/* ############### Valid test functions ###############*/
/* printGraph */
void case12_printGraph_null();

void case13_printGraph_no_edges();

void case14_printGraph_reflexive();

void case15_printGraph_second_j();

/* createGraph */
void case16_createGraph();

/* insertEdge*/
void case17_insertEdge();

/* removeEdge */
void case18_removeEdge();

#endif /* GRAPH_TESTS_H_ */
