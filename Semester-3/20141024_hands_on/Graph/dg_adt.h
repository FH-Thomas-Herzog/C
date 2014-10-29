/*
 * dg_adt.h
 *
 *	This is the header file which defines the interface for handling graphs.
 *
 *  Created on: Oct 12, 2014
 *      Author: cchet
 */

#ifndef DG_ADT_H_
#define DG_ADT_H_

#include "common.h"

/* The type representing the graph */
typedef struct Graph Graph;
/* Enums which are used for edge validation */
typedef enum EdgeInfo {
	EDGE_EXISTS, EDGE_NEW, EDGE_INVALID
} EdgeInfo;

/* Visitor function for visiting the nodes */
typedef void (*Visitor)(int source, int target, double weight);

/**
 * Creates a graph with the given size
 *
 * Graph **graph: the reference to created graph
 * int size: the maximum size of the graph. The graph cannot grow larger then this size.
 * return true if the creation was successful, false otherwise
 */
bool createGraph(Graph **graph, int size);

/**
 * Removes all of the nodes of this graph.
 *
 * Graph **graph: the references to the graph to be deleted.
 * return bool: true if the deletion was successful, false otherwise.
 * 				if the deletion was successful then the given references will be NULL
 */
bool deleteGraph(Graph **graph);

/**
 * Inserts a graph edge into the graph.
 *
 * Graph *graph: the where the node will be inserted
 * int source: the source node id which will reference the target
 * int target: the target node id which will be referenced by the source
 * double weight: the weight of the to insert node reference
 * return bool: true if the insert was successful, false otherwise
 */
bool insertEdge(Graph *graph, int source, int target, double weight);

/**
 * Removes a references between two graph nodes.
 *
 * Graph *graph: the graph where to delete the references
 * int source: the node id which references the target
 * int target: the node is which is referenced by the source
 * return bool: true if the deletion was successful, false otherwise
 */
bool removeEdge(Graph *graph, int source, int target);

/**
 * Prints the given graph.
 *
 * Graph *graph: the graph to be printed.
 * return bool: true if the graph could be printed
 */
bool printGraph(Graph *graph);

/**
 * Validates the edge for the given graph.
 *
 * Graph* graph: the graph to check for the valid edge
 * int source: the node id of the source
 * int target: the node id of the target
 * return EdgeInfo: the edge info enum which represents the function result.
 */
EdgeInfo validateEdge(Graph* graph, int source, int target);

/**
 * Visits all nodes in the graph if there is weighting present.
 * If a weighting is present the two nodes are connected to each other
 *
 * GRaph* graph: the graph to visit
 * Visitor visitor: the function pointer which provides the visitor logic
 */
void visitGraph(Graph* graph, Visitor visitor);

#endif /* DG_ADT_H_ */
