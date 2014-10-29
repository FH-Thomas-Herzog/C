/* includes the standard library */
#include <stdlib.h>
/* includes the standard I/O library */
#include <stdio.h>

/* Compile expects return type int if no return type is defined.
 * argc: the count of parameters
 * argv[]: the array containg the parameters 
*/
int main(int argc, char* argv[]) {
	/* variable declaration */
	int i=1;
	double k=2.0;

	// Wait program when wrong parameter count was defined
	if(argc != 2) {
		printf("Program requires 1 paramter !! ./<program_name> <int>\n\n");
		return 1;	
	}

	// Print entered parameter 
	printf("Param 1: %s \n", argv[1]);
	// Print hello world
	printf("Hello world!\n");
	// Print formatted text, numbers
	printf("integer: %3d , double: %3.2f \n", i, k);
	return 0;
}
