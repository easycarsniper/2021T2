// Program to test the Dictionary ADT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dict.h"
#include "WFreq.h"

int main(void) {
	Dict d = DictNew();
	DictInsert(d, "hello");
	assert(DictFind(d, "hello") == 1);
	
	// add more tests here
	int i = 0;
	int num = 300;
	while (i < num) {
		DictInsert(d, "alic");
		i++;
	}
	int count = DictFind(d, "alic");
	printf("num of alic: %d\n", count);

	i = 0;
	num = 30;
	while (i < num) {
		DictInsert(d, "voic");
		i++;
	}
	assert(DictFind(d, "voic") == 30);
	DictFree(d);
}

