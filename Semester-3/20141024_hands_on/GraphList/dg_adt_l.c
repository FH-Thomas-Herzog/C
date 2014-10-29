/*
 * dg_adt_l.c
 *
 * This is the implementation of of a directed graph for handling a weighted graph
 * by usage of an Adjazenzlist.
 *
 *  Created on: Oct 12, 2014
 *      Author: cchet
 */
#include <stdio.h>
#include <stdlib.h>
#include "dg_adt_l.h"
#include "common.h"

/* ####### local used functions ####### */

/**
 * Creates a weight node for the given id and weight.
 * This function does not care about the validity of the id and weight,
 * this is the responsibility of the caller.
 *
 * int id: the id of the referenced graph node
 * double weight: the weight for this edge
 * return WeightNode*: the create weight node with next and previous set to itself
 */
static WeightNode* createWeightNode(int id, double weight) {
	WeightNode* node = NULL;

	node = malloc(sizeof(WeightNode));
	/* Graph creation failed */
	if (!node) {
		printf("The weight node could not be created !!!\n");
		exit(EXIT_FAILURE);
	} /* if */

	node->id = id;
	node->weight = weight;
	node->next = node;
	node->previous = node;

	return node;
}

/**
 * Appends a weighting node to the list on the proper position,
 * so that the order of the references nodes is kept.
 *
 * WeightNode* list: the weighting list of the graph node
 * WeightNode* node: the node to insert into the list.
 */
static void appendWeightNode(WeightNode* list, WeightNode* node){
	WeightNode* temp = list->next;
	while((temp != list) && (temp->id < node->id)) {
		temp = temp->next;
	}
	node->next = temp;
	node->previous = temp->previous;
	temp->previous->next = node;
	temp->previous = node;
}

/**
 * Creates a graph node with the given id.
 * This function does not care about a valid node id, this is the responsibility of the caller.
 *
 * int id: the id of the graph node
 * return GRaphNode*: the created graph node with next and previous set to itself
 */
static GraphNode* createGraphNode(int id) {
	GraphNode* node = NULL;
	WeightNode* weightings;

	node = malloc(sizeof(GraphNode));
	/* Graph creation failed */
	if (!node) {
		printf("The graph node could not be created !!!\n");
		exit(EXIT_FAILURE);
	} /* if */

	weightings = createWeightNode(-1, -1);

	node->id = id;
	node->weightings = weightings;
	node->next = node;
	node->previous = node;

	return node;
}

/**
 * Deletes the weight node list.
 *
 * WeightNode* list: the weight node representing the list. (anchor element)
 */
static void deleteWeightNodeList(WeightNode** list) {
	WeightNode* node;
	WeightNode* next;

	if (list != NULL) {
		next = (*list);
		node = (*list)->next;
		while (node != (*list)) {
			next = node->next;
			free(node);
			node = next;
		} /* while */
		free((*list));
		(*list) = NULL;
	} /* if */
}

/**
 * Finds the graph node in the graph hold list.
 *
 * GRaph* graph: the graph to search for the node
 * int id: the id of the node to be found
 * return GraphNode*: the found node, null otherwise
 */
static GraphNode* findGraphNode(Graph* graph, int id) {
	GraphNode* node = NULL;

	/* Check for null graph */
	if (graph != NULL) {
		node = graph->list->next;
		while ((node != graph->list) && (node->id != id)) {
			node = node->next;
		} /* while */
		/* GraphNode not found */
		if (node == graph->list) {
			node = NULL;
		} /* if */
	} /* if */

	return node;
}

/**
 * Finds the edge in the graph.
 *
 * Graph* graph: the graph to search for the edge
 * int source: the source node holding the weighting
 * int target: the target which is referenced by the weighting entry.
 * return WeightNode*: the found node null, otherwise
 */
static WeightNode* findEdge(Graph* graph, int source, int target) {
	GraphNode* gNode;
	WeightNode* wNode;

	if (graph != NULL) {
		gNode = graph->list->next;
		while (gNode != graph->list) {
			/* source found */
			if (gNode->id == source) {
				wNode = gNode->weightings->next;
				while ((wNode != gNode->weightings) && (wNode->id != target)) {
					wNode = wNode->next;
				} /* while */
				/* target found */
				if (wNode != gNode->weightings) {
					return wNode;
				} else {
					return NULL;
				} /* if */
			} /* if */
			gNode = gNode->next;
		} /* while */
	} /* if */

	/* edge not found */
	return NULL;
}

/* ##################### public visible methods #####################*/
bool createGraph(Graph **graph, int size) {
	int i;
	GraphNode* nodeList;
	GraphNode* node;

	/* Graph references needs to be NULL */
	if ((*graph) != NULL) {
		printf("The given graph reference must be null !!!\n");
		return false;
	} /* if */

	/* Check for valid graph size */
	if (size <= 0) {
		printf("size must in range 0 < size < MAX_INT !!! size:%d !!!\n", size);
		return false;
	} /* if */

	/* Create graph */
	*graph = malloc(sizeof(Graph));
	nodeList = createGraphNode(-1);

	/* Add nodes to graph */
	for (i = 1; i <= size; ++i) {
		node = createGraphNode(i);
		node->next = nodeList;
		node->previous = nodeList->previous;
		nodeList->previous->next = node;
		nodeList->previous = node;
	} /* for */

	/* set graph attributes */
	(*graph)->list = nodeList;
	(*graph)->size = size;

	return true;
}

bool deleteGraph(Graph **graph) {
	GraphNode* node;
	GraphNode* next;

	if ((*graph) != NULL) {
		node = (*graph)->list->next;
		while (node != (*graph)->list) {
			next = node->next;
			deleteWeightNodeList(&(node->weightings));
			free(node);
			node = next;
		} /* while */
		(*graph)->list = NULL;
		free((*graph));
		(*graph) = NULL;
		return true;
	} /* if */

	return false;
}

bool insertEdge(Graph *graph, int source, int target, double weight) {
	WeightNode* weighting;
	GraphNode* node;
	EdgeInfo info;

	/* Check for null graph */
	if (graph == NULL) {
		printf("Cannot insert edge in NULL graph !!!\n");
		return false;
	} /* if */

	/* Check for valid weight */
	if (weight <= 0) {
		printf("Weight must be in range 0 < weight < MAX_DOUBLE !!!\n");
		return false;
	} /* if */

	/* handle result */
	info = validateEdge(graph, source, target);
	switch (info) {
	case EDGE_EXISTS:
		printf("Edge already exists. Remove it and afterwards add it !!!\n");
		return false;
		break;
	case EDGE_INVALID:
		printf(
				"Source and target must point to a valid graph node !!! source=%d, target=%d !!! \n",
				source, target);
		return false;
		break;
	case EDGE_NEW:
		appendWeightNode(findGraphNode(graph, source)->weightings, createWeightNode(target, weight));
		return true;
		break;
	default:
		printf("Unknown EdgeInfo instance detected !!!\n");
		exit(EXIT_FAILURE);
		break;
	} /* switch  */

	/* compiler wants it :) */
	return false;
}

bool removeEdge(Graph *graph, int source, int target) {
	WeightNode* weighting;
	EdgeInfo info;

	/* Check for null graph */
	if (graph == NULL) {
		printf("Cannot insert edge in NULL graph !!!\n");
		return false;
	} /* if */

	/* handle result */
	info = validateEdge(graph, source, target);
	switch (info) {
	case EDGE_EXISTS:
		weighting = findEdge(graph, source, target);
		weighting->previous->next = weighting->next;
		weighting->next->previous = weighting->previous;
		weighting->next = NULL;
		weighting->previous = NULL;
		free(weighting);
		return true;
		break;
	case EDGE_INVALID:
		printf(
				"Source and target must point to a valid graph node !!! source=%d, target=%d !!!\n",
				source, target);
		return false;
		break;
	case EDGE_NEW:
		printf("Edge not found !!!\n");
		return false;
		break;
	default:
		printf("Unknown EdgeInfo instance detected !!!\n");
		exit(EXIT_FAILURE);
		break;
	} /* switch */

	/* compiler wants it :) */
	return false;
}

bool printGraph(Graph *graph) {
	int i, lastVisited;
	GraphNode* gNode;
	WeightNode* wNode;

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
		gNode = graph->list->next;
		while (gNode != graph->list) {
			printf("%2i |", gNode->id);
			wNode = gNode->weightings->next;
			lastVisited = 1;
			while (wNode != gNode->weightings) {
				for (i = lastVisited; i < wNode->id; ++i) {
					printf("%5s%5s", "-", "");
				} /* for */
				printf("%3s%3.2f%3s", "", wNode->weight, "");
				lastVisited = wNode->id + 1;
				wNode = wNode->next;
			} /* while */
			for (i = lastVisited; i <= graph->size; ++i) {
				printf("%5s%5s", "-", "");
			} /* for */
			gNode = gNode->next;
			printf("\n");
		} /* while */

		return true;
	} /* if */
}

EdgeInfo validateEdge(Graph* graph, int source, int target) {
	/* Check for valid source and target */
	if ((target <= 0) || (target > graph->size) || (source <= 0)
			|| (source > graph->size)) {
		return EDGE_INVALID;
	} /* if */

	/* Check if edge already present */
	if (findEdge(graph, source, target) != NULL) {
		return EDGE_EXISTS;
	} /* if */

	return EDGE_NEW;
}

void visitGraph(Graph* graph, Visitor visitor) {
	WeightNode* wNode;
	GraphNode* gNode;

	if (graph != NULL) {
		gNode = graph->list->next;
		while (gNode != graph->list) {
			wNode = gNode->weightings->next;
			while (wNode != gNode->weightings) {
				if (wNode->weight != 0) {
					visitor(gNode->id, wNode->id, wNode->weight);
				} /* if */
				wNode = wNode->next;
			} /* while */
			gNode = gNode->next;
		} /* while */
	} /* if */
}
