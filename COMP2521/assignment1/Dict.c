// COMP2521 21T2 Assignment 1
// This program was written by Raphael Woo (z5360132)
// Dict.c ... implementation of the Dictionary ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "WFreq.h"

typedef struct dict_node* Dict_node;
// BST tree struct
struct dict_node{
	char *word; 
	int count;
	Dict_node left, right;
};

struct DictRep {
	Dict_node root; //pointer to the root node
};
 
//create a new tree using Dict_node
Dict_node new_dict(void) {
	return NULL;
}

//create new node for DictFindTopN
Dict_node n_node_count(char *word, int count) {
	Dict_node new_node = malloc(sizeof(*new_node));	
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->word = strdup(word);
	new_node->count = count;
	return new_node;
}

// create a new node with data and NULL left and right
Dict_node n_node(char *word) {
	Dict_node new_node = malloc(sizeof(*new_node));	
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->word = strdup(word);

	new_node->count = 1;
	return new_node;
}

// compute height of tree
int tree_height(Dict_node d) {
	if (d == NULL) {
		//if no node at all
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

//rotate the tree right
Dict_node rotate_right(Dict_node d) {
	if (d == NULL || d->left == NULL) {
		// if there is nothing to be turn 
		return d;
	}
	Dict_node d1 = d->left;
	d->left = d1->right;
	d1->right = d;
	return d1;
}

//rotate the tree left
Dict_node rotate_left(Dict_node d) {
	if (d == NULL || d->right == NULL) {
		// if there is nothing to be turn
		return d;
	}
	Dict_node d1 = d->right;
	d->right = d1->left;
	d1->left = d;
	return d1;
}

// free every node in the BST
void dict_node_free(Dict_node d) {
	if (d == NULL) {
		return;
	} else {
		dict_node_free(d->left);
		dict_node_free(d->right);
		free(d->word);
		free(d);		
	}
}

//insert the node from the root
Dict_node node_insert(Dict_node d, char *word) {
	if (d == NULL) {
		d = n_node(word);
	} else if (strcmp(word, d->word) < 0) {
		//go left if the word is smaller(lexicographic order)
		d->left = node_insert(d->left, word);
	} else if (strcmp(word, d->word) > 0) {
		//go right if the word is bigger(lexicographic order)
		d->right = node_insert(d->right, word);
	} else if (strcmp(word, d->word) == 0) {
		d->count++;
	}

	// balance when either side are too heavy
	int hL = tree_height(d->left);
	int hR = tree_height(d->right);
	if ((hL - hR) > 1) {
		//if left heavy
		if (strcmp(word, d->left->word) > 0) {
			//if the word is bigger than the word on the left
			d->left = rotate_left(d->left);
		}
		d = rotate_right(d);
	} else if ((hR - hL) > 1) {
		// if right heavy
		if (strcmp(word, d->right->word) < 0) {
			d->right = rotate_right(d->right);
		}
		d = rotate_left(d);
	}

	return d;
}

// Inserts an occurrence of the given word into the Dictionary
void DictInsert(Dict d, char *word) {	
	d->root = node_insert(d->root, word);
}

// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int dict_find(Dict_node d, char *word) {
	int count = 0;
	if(d == NULL) {
		return 0;
	} else if (strcmp(word, d->word) < 0) {
		return dict_find(d->left, word);
	} else if (strcmp(word, d->word) > 0) {
		return dict_find(d->right, word);
	} else if (strcmp(word, d->word) == 0) {
		count = d->count;
	}
	return count;
}

// insert data to tree, sort first by number of count (higher go left), 
// if same, then by lexicographic order
Dict_node node_insert_count(Dict_node d, char *word, int count) {

	if (d == NULL) {
		d = n_node_count(word, count);
		//printf(" word = %s ", word);
		//printf(" Inserted '%s' to the node\n", d->word);
	} else if (count > d->count) {
		//go right if the count is smaller
		d->left = node_insert_count(d->left, word, count);
	} else if (count < d->count) {
		//go left if the count is bigger
		d->right = node_insert_count(d->right, word, count);
	} else if (count == d->count) {
		// if they were the same
		if (strcmp(word, d->word) < 0) {
			//go left if the word is smaller
			d->left = node_insert_count(d->left, word, count);
		} else {
			d->right = node_insert_count(d->right, word, count);
		}
	}
	return d;
}

//loop through the d tree and copy every node to a new tree that will be sort in count
Dict_node copy_tree(Dict_node d, Dict_node c_tree) {
	if (d == NULL) {
		return c_tree;
	}
	c_tree = copy_tree(d->left, c_tree);
	c_tree = copy_tree(d->right, c_tree);
	c_tree = node_insert_count(c_tree, d->word, d->count);
	return c_tree;
}

// place the data into array, would stop either run of node or size >= n
int dict_node_insert_array(Dict_node d, WFreq *wfs, int size, int n) {
	if (size >= n) {
		return size;
	} else if (d == NULL) {
		return 1 + size;
	}
	size = dict_node_insert_array(d->left, wfs, size, n);
	if (size < n) {
		char *cpy_word = strdup(d->word);
		wfs[size].word = cpy_word;
		wfs[size].freq = d->count;
	}
	size = dict_node_insert_array(d->right, wfs, size, n);
	return size;
}

//return num of node in tree
int tree_num_node(Dict_node d) {
	if (d == NULL) {
		return 0;
	} else {
		return 1 + tree_num_node(d->left) + tree_num_node(d->right);
	}
}

// Creates a new Dictionary
Dict DictNew(void) {
	Dict tree = malloc(sizeof(*tree));
	assert(tree != NULL); // make sure there is enough memory for it
	tree->root = NULL;
	return tree;
}

// Frees the given Dictionary
void DictFree(Dict d) {
	if (d->root != NULL) {
		dict_node_free(d->root); 
	}
	free(d);
}

// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int DictFind(Dict d, char *word) {
	int count = dict_find(d->root, word);
	return count;
}

// Finds  the top `n` frequently occurring words in the given Dictionary
// and stores them in the given  `wfs`  array  in  decreasing  order  of
// frequency,  and then in increasing lexicographic order for words with
// the same frequency. Returns the number of WFreq's stored in the given
// array (this will be min(`n`, #words in the Dictionary)) in  case  the
// Dictionary  does  not  contain enough words to fill the entire array.
// Assumes that the `wfs` array has size `n`.
int DictFindTopN(Dict d, WFreq *wfs, int n) {	
	int size = -1;
	// create a new tree that will be sorted by count and lexicographic order
	// and copy every node from the old tree to the new one
	// then insert the data in the node to array based in that order 
	Dict_node count_tree = new_dict();
	count_tree = copy_tree(d->root, count_tree);
	size = dict_node_insert_array(count_tree, wfs, size, n);
	dict_node_free(count_tree);
	return size;	 
}

// Displays the given Dictionary. This is purely for debugging purposes,
// so  you  may  display the Dictionary in any format you want.  You may
// choose not to implement this.
void DictShow(Dict d) {
}

