#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int check(char* a, char* b, int (*comp) (char* a, char* b));
int numcmp (char* a, char* b);

int main (int argc, char** argv) {	
	char* s1 = "Test1";
	char* s2 = "TEst2";
	
	if (isalpha(*s1) || isalpha(*s2)){
			check(s1, s2, *strcmp);
	} else {
			check(s1, s2, numcmp);
	}
	return EXIT_SUCCESS;
}

int numcmp(char* a, char* b){
	if (atoi(a) == atoi(b)) {
		return 0;
	}else{
		return 1;
	}
}
