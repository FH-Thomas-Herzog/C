#include <stdlib.h>
#include <stdio.h>

#include "adtlist.h"


void printInt (int value) {
	printf("%d, ", value);
} /*printInt*/

void printDouble(double value) {
	printf("%f, ", value);
} /*printDouble*/


int main (){
	List *l = createList();
	
	prependList(l, 1);
	prependList(l, 213);
	prependList(l, 46);
	prependList(l, 75);
	prependList(l, 23);
	
	printf("forEach with printInt: \n");
	forEach(l, &printInt);
	printf("\n");
	
	/*forEach with printDouble produces an error with type mismatch*/
	/*
	printf("forEach with printDouble: \n");
	forEach(l, &printDouble);
	printf("\n");
	*/
	
	
	printf("printList: \n");
	printList(l);
	
	destroy(&l);
	
	return EXIT_SUCCESS;
} /*main*/
