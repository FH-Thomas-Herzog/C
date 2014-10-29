/*
 * dg_adt_tests_depend.h
 *
 *	This header file specifies the test dependencies which must
 *	be implemented by the tested implementation.
 *
 *  Created on: Oct 19, 2014
 *      Author: cchet
 */

#ifndef DG_ADT_TESTS_DEPEND_H_
#define DG_ADT_TESTS_DEPEND_H_

#include "dg_adt.h"

/**
 * Creates a test graph so that the tests are not depending on the
 * tested implementation. Don't implement it defensive but take care it
 * works as expected.
 *
 * int size: the size of the to create graph
 */
Graph* createTestGraph(int size);

/**
 * Inserts a edge in test graph so that the tests are not depending on the
 * tested implementation. Don't implement it defensive but take care it
 * works as expected.
 *
 * This functions does not need to check for valid edge, the test implementor is
 * responsible to take care of this.
 *
 * Graph* graph: the test graph to insert edge
 * int source, the source node id
 * int tagret: the target node id
 * double weight: the weight of the edge
 */
void insertTestEdge(Graph* graph, int source, int target, double weight);

#endif /* DG_ADT_TESTS_DEPEND_H_ */
