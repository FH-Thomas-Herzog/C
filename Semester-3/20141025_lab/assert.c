/* Disables all asserts */
#define NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* print the given number.
   Uses assert for assertation of the given number
*/
static void print_number(int* x) {
    /* Quits if the condition is false */
    assert(x != NULL);
    printf("x=%d\n", x);
} /* print_number */

int main (int argc, char** argv) {
    int a = 10;
    int* b = NULL;
    int* c= NULL;

    b = &a;

    print_number(b);
    print_number(c);
} /* main */
