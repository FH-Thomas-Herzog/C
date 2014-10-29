#ifndef __ADT_LIST_
#define __ADT_LIST_

typedef struct List List;

typedef void (*Iterator) (int value);

List* createList();
void prependList(List* list, int value);
void destroy(List **list);
void forEach(List *list, Iterator it);

#endif
