/*
 * This program will sum integer values which will have to be defined by 
 * program arguments.
 */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
	// Variable declaration
	int i = 0;
	int sum = 0;

	// Notify caller for missing arguments
	if(argc == 1) {
		printf("This program requires at least two integer arguments !!! E.g.: ./sum List<Int> \n");
		return 0;
	}

	for(i = 1; i < argc; i++) {
		// atoi does return 0 if the character is no valid number
		sum = sum + atoi(argv[i]);
	}
	
	printf("Sum: %1.2d\n", sum);
	return 0;
}
