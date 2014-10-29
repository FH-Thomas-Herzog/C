/*
 * dg_adt_l.h
 *
 *	This is the header for the implementation which uses a list for a
 *	graph representation. It enhances the dg_adt.h specification for the
 *	list specific helper functions.
 * Also it contains the concrete struct definition of the graph and used list nodes.
 *
 *  Created on: Oct 13, 2014
 *      Author: Thomas Herzog
 */

#ifndef DG_ADT_L_H_
#define DG_ADT_L_H_

#include "dg_adt.h"

typedef struct GraphNode GraphNode; /* Represents a node in the graph list */
typedef struct WeightNode WeightNode; /* Represents a weight node in the weighting list */

/* Realizes a double-cyclic list with anchor because easier to handle */
struct GraphNode {
	int id;
	WeightNode* weightings;
	GraphNode* next;
	GraphNode* previous;
};

/* Realizes a double-cyclic list with anchor because easier to handle */
struct WeightNode {
	int id;
	double weight;
	WeightNode* next;
	WeightNode* previous;
};

/* Graph here holds the list which holds the nodes */
struct Graph {
	GraphNode* list;
	int size;
};

#endif /* DG_ADT_L_H_ */
