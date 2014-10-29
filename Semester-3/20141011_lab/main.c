#include <stdlib.h>
#include <stdio.h>
#include "atg_list.h"

void PrintInt(int value) {
	printf("%d", value);
}

int main(){
	List* list = createList();
	prependList(list, 1);
	prependList(list, 17);
	prependList(list, 25);
	forEach(&list, &PrintInt);
	destroy(&list);
}

