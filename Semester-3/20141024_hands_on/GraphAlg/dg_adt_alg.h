/*
 * graph_algs.h
 *
 *	This header specifies the functionality of the graph algorithm source
 *	which performs operations on a graph.
 *
 *  Created on: Oct 13, 2014
 *      Author: cchet
 */

#ifndef GRAPH_ALGS_H_
#define GRAPH_ALGS_H_

#include "dg_adt.h"

/* Context control */
/**
 * Initializes the context for the graph operations.
 * The whole graph will be copied and on the copied graph the
 * operations will be performed
 *
 * Graph* graph: the graph to be initialize context on
 * int n: the size of the graph. Can be greater but not smaller than the size
 * of the given graph, otherwise an error will be thrown.
 */
bool initContext(Graph* graph, int n);

/**
 * Destroys the context by releasing all hold resources.
 */
bool destroyContext();

/* Context depended functions */
/**
 * Answers the question if the graph is reflexive.
 * Depends on an initialized context
 */
bool isReflexive();

/**
 * Answers the question if the graph is symmetric.
 * Depends on an initialized context
 */
bool isSymmetric();

/**
 * Answers the question if the graph is asymmetric.
 * Depends on an initialized context
 */
bool isAsymmetric();

/**
 * Answers the question if the graph is transitive.
 * Depends on an initialized context
 */
bool isTransitive();

/* context free functions */
/**
 * Will invert the graph nodes and copies the result in an own graph.
 */
Graph* invert(Graph* graph, int n);

/**
 * Prints all of the graph nodes which are connected with an edge
 * which weight > 0
 */
bool printGraphProperties(Graph* graph);

#endif /* GRAPH_ALGS_H_ */
