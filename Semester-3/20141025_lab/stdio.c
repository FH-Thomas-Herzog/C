#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void testIO() {
    int x, y, n;
    div_t z;

    FILE* f;

    /* Get console input */
    puts("Enter two numbers  separated by '/'\n");
    n = scanf("%d/%d", &x, &y);

    if(n < 2) {
        printf("Could not parse input\n");
        return;
    }

    /* Calculate division */
    z = div(x, y);

    printf("%d/%d = %d rem (%d)\n",x, y, z.quot, z.rem);

    /* Write int o file */
    f = fopen("division_result.dat", "wb");
    fwrite(&z, sizeof(div_t), 1, f);
    fclose(f);

    z = div(1234,1234);
    f = fopen("division_result.dat", "rb");

    /* Read from file */
    n = fread(&z, sizeof(div_t), 1, f);
    if(n < 1) {
        printf("Could not read file division_result.dat\n");
        return;
    }
    printf("%d/%d = %d rem (%d)\n",x, y, z.quot, z.rem);
    fclose(f);
}

static void testSeek(){
    FILE* f;
    long endOfWorld;
    char* line = NULL;
    size_t lineLength = 0;

    /* Write to created file */
    f = fopen("seek_test.txt", "w");
    fputs("Hello world\n", f);
    endOfWorld = ftell(f);

    fputs("How are you today?\n", f);
    fseek(f, 6, SEEK_SET); /* Get position 6 characters from start. This is the position were we want to be */
    fputs("Franz\n", f);
    fseek(f, endOfWorld, SEEK_SET);
    fputs("Fine Thanks!", f);
    fclose(f);

    /* Read from file */
    f = fopen("seek_test.txt", "r");
    line = NULL; /* Needs to be initalized otherwise an error will occur. Did ot work during lesson*/
    while(getline(&line, &lineLength, f) != -1) {
        printf("%d: %s", lineLength, line);
        free(line);
        line = NULL;
    }
}

int main(int argc, char** argv) {
    //testIO();
    testSeek();
    return EXIT_SUCCESS;
}
