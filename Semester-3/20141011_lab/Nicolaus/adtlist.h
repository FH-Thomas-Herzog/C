#ifndef __adtlist_h__
#define __adtlist_h__

typedef struct List List;
typedef void(*Iterator) (int value);

List* createList();
void prependList(List *l, int value);
void destroy(List **l);
void forEach(List *l, Iterator it);
void printList(List *l);

#endif
