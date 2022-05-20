// COMP2521 21T2 Assignment 1
// Dict.c ... implementation of the Dictionary ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "WFreq.h"

#define MAXWORD 100

// you may define your own structs here

typedef struct dict_node* Dict_node;
struct dict_node{
	char *word;
	//int id; // id will be define as the int that convert from the string
	int count;
	Dict_node left, right;
};

struct DictRep {
	Dict_node root; //pointer to the root node
	int size;
};

/*
typedef struct {
	int count;
	char *words;
}Dict_result;
*/

// add function prototypes for your helper functions here

// create a new node with data and NULL left and right
Dict_node n_node(char *word) {
	//int id = (int)*word;
/*
	int id = 0;
	char *word_id = word;
	while (*word_id != '\0') {
		id += (int)*word_id;
		word_id++;
	}
*/
	Dict_node new_node = malloc(sizeof(*new_node));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->word = word;
	new_node->count = 1;
	return new_node;
}

// compute height of tree
int tree_height(Dict_node d) {
	if (d == NULL) {
		//if no tree at all
		return 0;
	} else {
		//else find the height of left and right sub tree by 1 + call the function again 
		int lheight = 1 + tree_height(d->left);
		int rheight = 1 + tree_height(d->right);
		if (lheight > rheight) {
			return lheight;
		} else {
			return rheight;
		}
	}
}

// create a new node with NULL left and right
Dict new_node(char *word) {
	return NULL;
}

// Creates a new Dictionary
Dict DictNew(void) {
	Dict tree = malloc(sizeof(*tree));
	assert(tree != NULL); // make sure there is enough memory for it
	tree->root = NULL;
	tree->size = 0;
	return tree;
}

void dict_node_free(Dict_node d) {
	if (d != NULL) {
		dict_node_free(d->left);
		dict_node_free(d->right);
		free(d);
	}
}

// Frees the given Dictionary
void DictFree(Dict d) {
	Dict_node root = d->root;
	while (d->root != NULL) {
		dict_node_free(root); 
	}
}

//insert the node from the root
Dict_node node_insert(Dict_node d, char *word) {

	//printf("%s has word id = %d\n", word, id);
	if (d == NULL) {
		d = n_node(word);
		printf(" Inserted '%s'\n", d->word);
	} else if (strcmp(word, d->word) < 0) {
		//go left if the word is smaller
		d->left = node_insert(d->left, word);
	} else if (strcmp(word, d->word) > 0) {
		//go right if the word is bigger
		d->right = node_insert(d->right, word);
	} else if (strcmp(word, d->word) == 0) {
		d->count++;
	}
	return d;
}

// Inserts an occurrence of the given word into the Dictionary
void DictInsert(Dict d, char *word) {	
	/*
	Dict_node root = d->root;
	if (root == NULL) {
		root = n_node(word);
		d->root = root;
	} else {
		d->root = node_insert(root, word);
	}
	d->size++;
	*/
	d->root = node_insert(d->root, word);
	d->size++;
	//printf(" Inserted '%s'\n", word);
}

// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int DictFind(Dict d, char *word) {
	/*
	int count;
	long id = strtol(word, NULL, 10);
	if(d == NULL) {
		return 0;
	} else if (id < d->id) {
		return DictFind(d->left, word);
	} else if (id > d->id) {
		return DictFind(d->right, word);
	} else if (id == d->id) {
		count = d->count;
	}
	return count;
	*/
	return 0;
}

// Finds  the top `n` frequently occurring words in the given Dictionary
// and stores them in the given  `wfs`  array  in  decreasing  order  of
// frequency,  and then in increasing lexicographic order for words with
// the same frequency. Returns the number of WFreq's stored in the given
// array (this will be min(`n`, #words in the Dictionary)) in  case  the
// Dictionary  does  not  contain enough words to fill the entire array.
// Assumes that the `wfs` array has size `n`.
int DictFindTopN(Dict d, WFreq *wfs, int n) {
	return 0;
}

void dict_node_print(Dict_node d) {
	if (d == NULL) {
		return;
	}
	dict_node_print(d->left);
	printf("%s has count %d\n", d->word, d->count);
	dict_node_print(d->right);
}

int tree_num_node(Dict_node d) {
	if (d == NULL) {
		return 0;
	} else {
		return 1 + tree_num_node(d->left) + tree_num_node(d->right);
	}
}

// Displays the given Dictionary. This is purely for debugging purposes,
// so  you  may  display the Dictionary in any format you want.  You may
// choose not to implement this.
void DictShow(Dict d) {
	dict_node_print(d->root); 
	printf("Num insert call size = %d\n", d->size);
	int num_node = tree_num_node(d->root);
	printf("Tree num node = %d\n", num_node);

	/*
	DictShow(d->root->left);
	printf("%s has count %d", d->word, d->count);
	DictShow(d->root->right);
	*/
	
}

