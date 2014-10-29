/*
 * dg_adt_tests.c
 *
 * This source provides the implementation depending functions for the tests.
 *
 *  Created on: Oct 12, 2014
 *      Author: cchet
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dg_adt_tests_depend.h"
#include "dg_adt_l.h"

static WeightNode* createTestWeightNode(int id, double weight) {
	WeightNode* node = NULL;

	node = malloc(sizeof(WeightNode));
	node->id = id;
	node->weight = weight;
	node->next = node;
	node->previous = node;

	return node;
}

static GraphNode* createTestGraphNode(int id) {
	GraphNode* node = NULL;
	WeightNode* list;

	node = malloc(sizeof(GraphNode));
	list = createTestWeightNode(-1, -1);
	/* Make to anchor node */
	node->id = id;
	node->weightings = list;
	node->weightings->next = node->weightings;
	node->weightings->previous = node->weightings;
	node->next = node;
	node->previous = node;

	return node;
}

Graph* createTestGraph(int size) {
	int i;
	Graph* graph;
	GraphNode* node;

	graph = malloc(sizeof(Graph));
	node = createTestGraphNode(-1);

	/* Set attributes on graph */
	graph->size = size;
	graph->list = node;

	for (i = 1; i <= size; ++i) {
		node = createTestGraphNode(i);
		node->next = graph->list;
		node->previous = graph->list->previous;
		graph->list->previous->next = node;
		graph->list->previous = node;
	} /* for */
	return graph;
}

void insertTestEdge(Graph* graph, int source, int target, double weight) {
	WeightNode* wNode;
	WeightNode* temp;
	GraphNode* gNode;

	gNode = graph->list->next;
	while ((gNode != graph->list) && (gNode->id != source)) {
		gNode = gNode->next;
	} /* while */

	wNode = createTestWeightNode(target, weight);
	temp = gNode->weightings->next;
	while((temp != gNode->weightings) && (temp->id < wNode->id)) {
		temp = temp->next;
	} /* while */
	wNode->next = temp;
	wNode->previous = temp->previous;
	temp->previous->next = wNode;
	temp->previous = wNode;
}

