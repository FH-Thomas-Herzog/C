#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(int argc, char** argv) {
    printf("sizeof(size_t)=%d\n", sizeof(size_t));
    printf("sizeof(ptrdiff_t)=%d\n", sizeof(ptrdiff_t));
    printf("sizeof(wchar_t)=%d\n", sizeof(wchar_t));
    printf("sizeof(int)=%d\n", sizeof(int));
    printf("sizeof(float)=%d\n", sizeof(float));
    printf("sizeof(double)=%d\n", sizeof(double));
}
