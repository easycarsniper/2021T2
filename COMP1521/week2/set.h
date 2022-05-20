#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdbool.h>
 
typedef struct SetRep *Set;
 
// ADT functions go here
Set SetCreate(); // create a new set
void SetInsert(Set, int); // add number into set
void SetDelete(Set, int); // remove number from set
int SetMember(Set, int); // set membership test
int SetCard(Set); // size of set
Set SetUnion(Set, Set); // union
Set SetIntersect(Set, Set); // intersection
void SetDestroy(Set); // destroy a created set

	
// others
Set SetCopy(Set);          // make a copy of a set
void SetShow(Set); 

#endif	
