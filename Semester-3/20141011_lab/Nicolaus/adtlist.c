#include <stdlib.h>
#include <stdio.h>

#include "adtlist.h"

typedef struct Node {
	int value;
	struct Node* next;
} Node; /*typedef*/

struct List {
	Node* first;
	int n;
}; /*struct*/

List* createList() {
	List* l = (List*) malloc (sizeof(List));
	if (!l) {
		return NULL;
	} /*if*/
	l -> first = NULL;
	l -> n = 0;
	return l;
}

static Node* createNode(int value) {
	Node* n = (Node*) malloc(sizeof(Node));
	if (!n) {
		return NULL;
	} /*if*/
	
	n -> value = value;
	n -> next = NULL;
	
	return n;
} /*createNode*/

void prependList(List *l, int value) {
	Node* n = createNode(value);
	if(!n) {
		return;
	} else {
		n -> next = l -> first;
		l -> first = n;
		l -> n += 1;
	} /*if*/
}

void destroy(List **l) {
	Node* current;
	Node* next;
	
	if (*l == NULL) /*List doesn't exist*/
		return; 
	
	current = (*l) -> first;
	
	while (current != NULL) {
		next = current -> next;
		free(current);
		current = next;
	} /*while*/
	
	free(*l);
	*l = NULL;
} /*destroy*/

static void printNode(Node *n) {
	printf("@%p (%d, next -> %p)", (void*)n, n -> value, ((void*)n -> next));
} /*printNode*/

void printList(List *l) {
	
	Node* current;
	
	printf("@%p (first -> %p, Elements: %d)\n", (void*)l, ((void*)l -> first), l -> n);
	current = l -> first;
	while (current != NULL) {
		printNode(current);
		current = current -> next;
		if (current != NULL) {
			printf(", ");
		} /*if*/
	} /*while*/
	printf("\n");
} /*printList*/

void forEach(List* l, Iterator it) {
	Node* current = l -> first;
	
	while (current != NULL) {
		it(current -> value);
		current = current -> next;
	} /*while*/
} /*forEach*/
