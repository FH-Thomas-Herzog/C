#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static double doSum(int count, ...){
    double sum = 0.0;
    double temp;
    int i;

    /* init list for arguments */
    va_list args;
    /* ini the list with count arguments */
    va_start(args, count);

    /* Iterator over the arguments */
    for(i = 0; i< count; i++) {
        /* get the next argument */
        temp = va_arg(args, double);
        printf("temp=%g\n", temp);
        sum += temp;
    }
    /* end iteration over arguments */
    va_end(args);

    return sum;
}

int main(int argc, char** argv) {
    printf("doSum=%g\n", doSum(1, 0));
    printf("doSum=%g\n", doSum(2, 1.0, 2.0));
    printf("doSum=%g\n", doSum(3, 1.0, 2.0, 3.0));
    printf("doSum=%g\n", doSum(4, 1.0, 2.0, 3.0, 4.0));
    return 0;
}
