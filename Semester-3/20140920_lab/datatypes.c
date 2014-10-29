#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h> /* System include = system lib */
#include "datatypes.h" /* User include = User lib. Relative or absolute paths are possible, defines can be placed there to */

/* Define constans for the c program */
/* !!! This is for the preprocessor                        !!! */
/* !!! These are no variables, no memory or stacck is used !!! */
/* Preprocessor replaces literals with defined values in the text representation of the programm */
#define EINS 1
#define ROWS 3
#define COLS 3
#define PI 3.1415926f
/* No boolean not available in C */
#define TRUE 1
#define FALSE 0
/* Will replace defined text with the expression */
#define IS_POSITIVE(a) ((a) >= 0 ? TRUE : FALSE)

/* Enumeration which represents the bool type */
/* !!! false = 0, must always be integer type !!! */
typedef enum bool {false = 0, true = 1} bool;

/* These are variables */
const int cPI = 3.1415926f;
/* Globale variablen */
char c;
short s;
unsigned short us;
int i;
float f;
double d;
static long l; /* key word 'static' only accessible within this file and cannot be accessed by another file */


int main (int argc, char** argv) {

	/* Every variable within two bracets represent a context and will not exists outsite the context */
	{
		int c = 39; /* shadowed variable, shadows global variable 'c' */
		printf("c= %i\n", c);
	}
	printf("c= %i\n", c);

	TestDefines();
	printf("----------------------------\n");
	TestVariables();
	printf("----------------------------\n");
	TestArrayID();
	printf("----------------------------\n");
	TestArrayID();
	printf("----------------------------\n");
	TestArrayID();
	printf("----------------------------\n");
	TestArray2D();
	printf("----------------------------\n");
	TestStrings();

	printf("\n");
	return EXIT_SUCCESS;
}

/* Default with no params is void, so need to define it */
void TestDefines(void) {
	int num;
	int retVal;

	printf("Enter a number: ");
	/* Read valud and assigned it to num &num is the address of the variable because of call by value issue */
	retVal = scanf("%d", &num);

	if (retVal > 0) {
		printf("%d * pi is %4.2f und %s\n", num, (num * PI), IS_POSITIVE(num) ? " positiv " : " negative ");
	} else {
		printf("Error invalid input !!! Error-code: %i", retVal);
	} /* if */
}

void TestVariables(void) {
	printf("Truncation and overflow:\n");

	s = -3.5; 
	printf("s = 3.5; s -> %d (truncated)\n", s);

	printf("SHRT_MIN = %d \n", SHRT_MIN);
	
	us = -1;
	printf("us = -1 -> us: %d \n", us);

	/* Implicit type conversion, take care of this. */
	us = 2;
	s = 3;
	f = s / us;
	printf("3/2 -> integer division %4.2f \n", f);
		
	f = ((float) s) / us; /* Because of the cast to float this division will become a float division */
	printf("3/2 -> float  division %4.2f \n", f);

	d = 5 * 2.0; /* -> double division */
	f = 5 * 2.0f; /* -> float */
	l = 5  * 2l; /* -> long */
	i = 5  * 20u; /* ->  unsigned int */
	i = 5 * 2; /* -> integer */

	printf("Bit operations: \n");
	i = 0x000F;
	printf("i = 0x000F -> i = 0x%X \n", i);
	
	i = 0x000A | 0x0001;
	printf("i = 0x000A | 0x0001 -> i = 0x%X \n", i);
	
	i = 0x000A & 0x0001;
	printf("i = 0x000A & 0x0001 -> i = 0x%X \n", i);
	
	i = 0x000A ^ 0x0001;
	printf("i = 0x000A ^ 0x0001 -> i = 0x%X \n", i);		
}

void PrintArray1D(int a[], int size) {
	int i;
	printf("1D Array:\n");	
	for (i = 0 ; i < size; i++) {
		printf("a[%i]: %i \n", i, a[i]);
	} /* for */
	/* Display call by value issue */
	/* Arrays are always pointer in C and therefore call by value will take place on the pointer address and not the array itself */
	a[3] = 47;
}

void TestArrayID(void) {
	static int count = 0; /* Static varibale which is accessible over multiple calls within this function, but not accessible by another context */

	int a[] = {1,2,3,4,5,6}; /* Automatisch variablen are non-static and will be automatically deleted after cotnext destroy. */
	PrintArray1D(a, 6);
	int i;
	printf("1D Array:\n");	
	for (i = 0 ; i < 6; i++) {
		printf("a[%i]: %i \n", i, a[i]);
	} /* for */

	count++;
	printf("Number of invocations: %d", count);
}

void TestArray2D(void) {
	int i, j;
	int rows = 3;
	int cols = 5;
	int a[][5] = {{1,2,3,4,5},
		{6,7,8,9,10},
		{11,12,13,14,15}};
	
	printf("Size of Array: -> %d Bytes, %d Numbers \n", sizeof(a), sizeof(a) / sizeof(int));
	printf("2D Array \n");
	for (i = 0 ; i < rows; i++) {
		for (j = 0 ; j < cols; j++) {
			printf("a[%i][%i]: %i \n", i, j, a[i][j]);
		} /* for */
	} /* for */
}

void TestStrings(void) {
	char charArray[64];
	char string[] = " macht Spass !\n";
	/* Pointer notation: 'char * string = " macht Spass!\n"' */

	charArray[0] = 'p';
	charArray[1] = 'r';
	charArray[2] = 'o';
	charArray[3] = '\0'; /* Terminates the string. Reserved for this usage '\0' = Termination symbol*/
	printf("CharArray: %s; strlen(charArray): %d; sizeof(charArray): %d\n", charArray, strlen(charArray), sizeof(charArray));

	strcat(charArray, "grammieren");
	strcat(charArray, string);
	printf("CharArray: %s; strlen(charArray): %d; sizeof(charArray): %d\n", charArray, strlen(charArray), sizeof(charArray));

	sprintf(charArray, "Alles neu, %s%c", string, '!');
	printf("CharArray: %s; strlen(charArray): %d; sizeof(charArray): %d\n", charArray, strlen(charArray), sizeof(charArray));

	strcpy(charArray, string);
	printf("CharArray: %s; strlen(charArray): %d; sizeof(charArray): %d\n", charArray, strlen(charArray), sizeof(charArray));

	if (strcmp(charArray, string) == 0) {
		printf("CharArray equal to string !!!\n");
	} else {
		printf("CharArray not equal to string !!!\n");
	} /* if */

	printf("Das ist ein"  " abgeteiltes String"  " literal");
}



