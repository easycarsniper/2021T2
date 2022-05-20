#include "set.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMS 10000

struct SetRep {
    int elems[MAX_ELEMS];
    int nelems;
};

Set SetCreate() { 
    	
    Set s = malloc(sizeof(struct SetRep));
    if (s == NULL) {
         fprintf(stderr, "Insufficient memory\n");
         exit(1);
    }
    s->nelems = 0;
    // assert(isValid(s));
    return s;
}

void SetInsert(Set s, int item) {
    for (int i = 0; i < s->nelems; i++) {
        if (s->elems[i] == item) return;
    }
    s->elems[s->nelems] = item;
    s->nelems++;
}

void SetShow(Set) {
    printf("{");
    for (int i = 0; i < s->nelems; i++) {
        printf("%d", s->elems[i]);
        if (i < s->nelems-1) {
            printf(",");
        }
    }
    printf("}");
}
/* 


void SetDelete(Set, int) { ... }
int SetMember(Set, int) { ... }
int SetCard(Set) { ... }
Set SetUnion(Set, Set) { ... }
Set SetIntersect(Set, Set) { ... }
void SetDestroy(Set) { ... }
/*