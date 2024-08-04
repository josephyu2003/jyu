/* 
 * File:	list.c
 *
 * Copyright:	2022, Joseph Yu
 *
 * Description:	This file contains the implementation of the linked list object
 * 		declared in list.h. It will serve to form the backbone for
 * 		radix.c, maze.c, and the generic hash-chain set ADT used for 
 * 		unique.c and parity.c 
 *
 */

// Import mods
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "list.h"

/* struct list: contains a pointer to the head, along with the number
 * 		of elements and an optional function */
struct list {
	int count;
	struct node *head;
	int (*compare)();
};

/* struct node: contains a generic piece of data along with pointers to the
 * 		next and previous nodes */
typedef struct node {
	void *data;
	struct node *next;
	struct node *prev;
} NODE;

/* static LIST createNode(void *item): creates a node with the given data
 * 				       -> O(1), since no iteration is required */
static NODE *createNode(void *item, NODE *prev, NODE *next) {
	
	// Create the node and assign the data to it
	NODE *np = (NODE *)malloc(sizeof(NODE));
	np->data = item;
	np->prev = prev;
	np->next = next;
	
	// Return the node
	return np;	

}

/* LIST createList(): creates a new LIST value with the given compare function 
 * 		      -> O(1), since intialization in this case doesn't require
 * 		       iteration */
LIST *createList(int (*compare)()) {

	// Declare the list and define its attributal values
	LIST *lp = (LIST *)malloc(sizeof(LIST));
	lp->head = createNode(NULL, NULL, NULL);
	lp->count = 0;
	lp->compare = (*compare)();

	// Return the list
	return lp;

}

/* void destroyList(LIST *lp): destroys the LIST by deallocating all of its
 * 			       nodes and freeing the list itself 
 * 			       -> O(n), since all of the nodes in the list
 * 			       have to be iterated through*/
void destroyList(LIST *lp) {

	// Loop the list through the head and free nodes iteratively	
	assert (ls != NULL);
	NODE *np = lp->head->next, *temp;   
	while (np != NULL && np->data != NULL) {
		temp = np;
		np = np->next;
		free(temp);	
	}
	
	// Free the struct itself
	free(lp);
	
}

/* int numItems(LIST *lp): merely returns the list's count
 * 			   -> O(1), since it simply returns a value */
int numItems(LIST *lp) {
	assert(lp != NULL);
	return lp->count;
}


/* void addFirst(LIST *lp, void *item): adds a node to the list's start with
 *					the given data
 *					-> O(1), since the rest of the list does 
 *					not change and nothing is iterated. */
void addFirst(LIST *lp, void *item) {
	assert(lp != NULL && item != NULL);
		
	// Create the node to be added
	NODE *np = createNode(item, lp->head, lp->head->next);

	// Attatch the node onto the list
	lp->head->next->prev = np;
	lp->head->next = np;
	if(lp->head->prev == NULL) lp->head->prev = np;
	lp->count++;

}

/* void addLast(LIST *lp, void *item): add a node to the list's end with
 * 				       the given data
 * 				       -> O(1), since it's similar to addFirst() */
void addLast(LIST *lp, void *item) {

	assert(lp != NULL && item != NULL);

	// (Similar to addFirst, but to the list's end rather than start)
	NODE *np = createNode(item, lp->head->prev, lp->head);
	lp->head->prev->next = np;
	lp->head->prev = np;
	if(lp->head->next == NULL) lp->head->next = np;
	lp->count++;

}

/* void *removeFirst(LIST *lp): remove the first node from the list and 
 * 				return its value
 * 				-> O(1), since no iteration is involved */
void *removeFirst(LIST *lp) {
	
	assert(lp != NULL);
	
	// Locate the first node and rearrange the linked list to exclude it
	NODE *temp = lp->head->next;
	lp->head->next = lp->head->next->next;

	// Extract its value, free the node, and return the value
	void *data = temp->data;
	free(temp);
	lp->count--;
	return data;
		
}

/* void *removeLast(LIST *lp): remove the last node from the list and
 * 			       return its value
 * 			       -> O(1), since it's similar to removeFirst() */
void *removeLast(LIST *lp) {
	
	assert(lp != NULL);

	// (Similar to removeFirst(), but the last node is considered)
	NODE *temp = lp->head->prev;
	lp->head->prev = lp->head->prev->next;
	void *data = temp->data;
	free(temp);
	lp->count--;
	return data;

}

/* void *getFirst(LIST *lp): return the first item of the list 
 * 		             -> O(1), since it just returns a value */
void *getFirst(LIST *lp) {
	assert(lp->count > 0);
	return lp->head->next->data;
}

/* void *getLast(LIST *lp): return the last item of the list 
 * 			    -> O(1), since it is similar to getFirst()*/
void *getLast(LIST *lp) {
	assert(lp->count > 0);
	return lp->head->prev->data;
}

/* void *getItems(LIST *lp): return an array of the list
 * 			     -> O(n), since all of the values have to be allocated
 * 			     into the array through iteration */
void *getItems(LIST *lp) {
	
	assert(lp != NULL)
		
	// Initial iteration variable and the return value
	NODE *np = lp->head->next;
	void *nplist[lp->count];
	int i = 0;

	// Loop through the linked list and add to the array
	while (np != NULL && np->data != NULL) {
		nplist[i] = np->data;
		np = np->next;
		i++;
	} 
	
	// Return the array
	void *retarr;
	memcpy(&retarr, &nplist, lp->count*sizeof(void *));
	return retarr;

}
