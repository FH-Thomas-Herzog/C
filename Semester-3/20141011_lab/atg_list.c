#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atg_list.h"

typedef struct Node {
	int value;
	struct Node* next;
} Node;

typedef struct List{
	struct Node* node;
	int count;
} List;

static void PrintList(List* list);
static void PrintNode(Node* node) ;

List* createList(){
	List* list = (List*) malloc(sizeof(List));
	if (!list) {
		return NULL;
	}
	list->node = NULL;
	list->count = 0;
	return list;
}

static Node* createNode(int value) {
	Node* node = (Node*) malloc(sizeof(Node));
		if (!node) {
			return NULL;
		}
	node->value = 0;
	return node;
}

void prependList(List* list, int value){
	Node* node = createNode(0);
	if(!node){
		/* handle error */
	}else {
		node->next = list->node;
		list->node = node;
		list->count +=1;
	}
}

void destroy(List** list){
	Node* next;
	Node* current;
	
	if((*list) != NULL){
		PrintList(*list);
		current = (*list)->node;
		while (current  != NULL){
			next = current->next;
			free(current);
			current = next;
		}
	}
	
	free(*list);
	*list = NULL;
}

static void PrintList(List* list) {
	Node* next = NULL;
	Node* current = NULL;
	
	printf("@%p(Elements; %d, first->%p))*", (void*) list, list->count, (void*) list->node);
	next = list->node;
	while(current != NULL){
		PrintNode(current);
		next = current->next;
		if (current != NULL) {
			
		}
		current = next;
	}
}

static void PrintNode(Node* node) {
	printf("@%p(%d, ->%p))*", (void*) node, node->value, (void*) node->next);
}
