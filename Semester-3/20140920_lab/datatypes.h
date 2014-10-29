#ifndef _ULIBC_DATATYPES_H_ /* If marker not defined then the marker will be set and the header file will be included */
#define _ULIBC_DATATYPES_H_ /* Marker which will be set by the preprocessor and used for avoiding mulitple includes of the header */

/* This header file declares the used function in the main programm which has to include this header file */
/* Declare function because before implemented */
void TestDefines(void);
void TestVariables(void);
void PrintArray1D(int[], int); /* Variable not needed just type. Useful when encapsulated inot header file */
void TestArrayID(void);
void TestArray2D(void);
void TestStrings(void);

#endif /* Otherwise header file is ignored */
