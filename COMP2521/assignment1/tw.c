// COMP2521 21T2 Assignment 1
// This program was written by Raphael Woo (z5360132)
// tw.c ... compute top N most frequent words in file F
// Usage: ./tw [Nwords] File

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "stemmer.h"
#include "WFreq.h"

#define MAXLINE 1000
#define MAXWORD 100

#define NOT_INIT 0
#define INIT 1
#define ENDED 2
#define TRUE 0
#define FALSE 1

#define isWordChar(c) (isalnum(c) || (c) == '\'' || (c) == '-')

FILE* open_file(char *argv[], int n);
Dict read_text(FILE *fp, Dict dict);
void normalising(char *line);
Dict tokenising(char *line, Dict dict);
Dict stopword_removal(char *token, Dict dict);
void store_word(char *token, Dict word_tree);

int main(int argc, char *argv[]) {
	int   nWords = 10;    // number of top frequency words to show, default is 10
	FILE *fp; 		 // type file 
	Dict word_dict = DictNew();

	// process command-line args
	switch (argc) {
		case 2:
			nWords = 10;
			fp = open_file(argv, 1);
			break;
		case 3:
			nWords = atoi(argv[1]);
			if (nWords < 10) nWords = 10;
			fp = open_file(argv, 2);
			break;
		default:
			fprintf(stderr,"Usage: %s [Nwords] File\n", argv[0]);
			exit(EXIT_FAILURE);
	}
	WFreq top_word[nWords];
	word_dict = read_text(fp, word_dict);

	int size_array = DictFindTopN(word_dict, top_word, nWords);
	int i = 0;
	for (i = 0; i < size_array; i++) {
		printf("%d %s\n", top_word[i].freq, top_word[i].word);
		free(top_word[i].word);
	}

	fclose(fp);
	DictFree(word_dict);

}

//open and read the file, if file name is not existent/unreadable, return error messages
FILE* open_file(char *argv[], int n) {
	FILE *fp = fopen(argv[n], "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	return fp;
}

//read text from the file and when it reach the actual text, process it
Dict read_text(FILE *fp, Dict dict) {
	char line[MAXLINE + 1];
	char start_process_string[MAXLINE] = "*** START OF THIS PROJECT GUTENBERG EBOOK";
	char end_process_string[MAXLINE] = "*** END OF THIS PROJECT GUTENBERG EBOOK";
	char *start_process;
	char *end_process;
	int processing = NOT_INIT;
	while (fgets(line, MAXLINE + 1, fp) != NULL) {
		// for every line before a newline or reach MAXLINE
		start_process  = strstr(line, start_process_string);
		end_process = strstr(line, end_process_string);
		if (end_process == NULL && processing == INIT) {
			//if it has not reach the end of text
			// then start process the text
			
			dict = tokenising(line, dict);
			
		} else if (end_process != NULL && processing == INIT) {
			//if it reach the end of text message after reaching the start of text message
			processing = ENDED;
		}
		if (start_process != NULL) {
			//if it reach the actual text
			processing = INIT;			
		}	
	}
	if (processing != ENDED) {
		// if it has not encountered *** END OF line
		// or *** START OF line
		//priint error message
		fprintf(stderr, "Not a Project Gutenberg book\n");
		exit(EXIT_FAILURE);
	}
	return dict;	
}

// tokenising the line into words
Dict tokenising(char *line, Dict dict) {
	char *token;
	token = strtok(line, " \n\t()\",!{}[]._^;:*`~?");
	// loop through the string to extract all token
	while (token != NULL) {
		normalising(token);
		// to ignore any null terminator by empty line
		if (strlen(token) > 1) {
			dict = stopword_removal(token, dict);
		}
		
		token = strtok(NULL, " \n\t()\",!{}[]._^;:*`~?");
	}
	return dict;
}


// normalising the string
void normalising(char *line) {
	if (line == NULL) {
		// if there is no string in the pointer
		return;
	}
	char *nline = line;
	//normalising
	while (*line != '\0') {
		//if the char are not the one we need to remove, the two pointer 
		//move one together, otherwise, only the line pointer will move one
		if (isWordChar(*line) == 1) {
			// line == alphabet, num, hyphen, and single quote
			if (*line >= 'A' && *line <= 'Z') {
				//if upper case alphabetics
				// normalising by add 32
				*line = *line + 32;
			}
			*nline++ = *line;	
		} 
		line++;
	}
	*nline = '\0'; // add a null to the nline pointer to finish the sentence
}

// check if the word are in the stopword file 
// do nothing if it is in it
// if not stem it then store it into the dict
Dict stopword_removal(char *token, Dict dict) {
	int is_stopword = FALSE;
	FILE *sfp = fopen("stopwords", "r");
	if (sfp == NULL) {
		//if cannot find stepwords file
		fprintf(stderr, "Can't open stopwords\n");
		exit(EXIT_FAILURE);
	}
	char stopword[MAXWORD];
	while (fgets(stopword, MAXLINE, sfp) != NULL) {
		//while there is still words in the stopword file 
		//check if they match the input
		stopword[strlen(stopword) - 1] = '\0';
		if (strcmp(stopword, token) == 0) {
			// if input and stopword match
			// skip this word and break out to reduce looping time
			is_stopword = TRUE;
			break;
		}	
	}
	if (is_stopword == FALSE) {
		// if token != stopword
		// stem it
		// then send it to the dict
		int strleng = strlen(token);
		stem(token, 0, strleng - 1);
		DictInsert(dict, token);
	}
	fclose(sfp);
	return dict;
}
