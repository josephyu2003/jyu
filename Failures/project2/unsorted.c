/*
 * File:	unsorted.c
 *
 * Copyright:	2021, Joseph Yu
 *
 * Descripton:	This file defines the public functions listed under "set.h" to
 * 		set up the internal framework for an UNSORTED set abstract 
 * 		data type.
 */

/* Mods and Definitions */
# include <assert.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "set.h"

/* 
 * Struct "SET"
 * -> int "max": maximum number of elements
 * -> int "count": count of current elements 
 * -> char ** "array": list of unsorted
 */
struct set {
	int max;
	int count;
	char **array;
};
static int search()

/*
 * Function "createSet(int maxElts)"
 * Purpose: creates a new set pointer with desired length of "maxElts"
 * Big-O: O(1)
 */
SET *createSet(int maxElts) {
	SET *newSet = malloc(sizeof(SET));
	newSet->max = maxElts;
	newSet->array = malloc(sizeof(char *) * maxElts);
	newSet->count = 0;
	return newSet;
}

/* 
 * Function: "destroySet(SET *sp)"
 * Purpose: destroys a old set pointed by the variable sp
 * Big-O: O(n), since every element must be deallocated separately
 */
void destroySet(SET *sp) {
	free(sp);
}

int numElements(SET *sp) {
	return sp->count;
}

char *findElement(SET *sp, char *elt) {
	int i;
	for (i=0;i<sp->count;i++) {
		if (strcmp(sp->array[i],elt) == 0) return elt;
	}
	return NULL;
}

void addElement(SET *sp, char *elt) {
	if (sp->count == sp->max) return;
	if (findElement(sp,elt) != NULL) return; 
	sp->array[sp->count] = strdup(elt);
	assert(sp->array[sp->count]);
	sp->count++;
}

void removeElement(SET *sp, char *elt) {
	int i,index = -1;
	for (i=0;i<sp->count;i++) {
		if (strcmp(sp->array[i],elt) == 0) {
			index = i;
			break;
		}
	}
	if (index == -1) return;
	for (i=index;i<sp->count-1;i++){
		sp->array[i] = sp->array[i+1];
	}				
}	


//To-do: use "memcpy"
char **getElements(SET *sp) {
	return sp->array;
}

