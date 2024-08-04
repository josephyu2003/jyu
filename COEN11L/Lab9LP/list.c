/* Mods */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "lab9.h"

/* list.c - file containing functions that directly interact with the data pertaining to the contacts */

/* insert - creates a new contact, and, through iteration, ensures that the name is not a duplicate and places it into the appropriate *
*           alphabetical position in the linked-lists under LETTER_HEAD_CONTACT_NODES.*/
void insert(char newName[50], char newPhoneNumber[50]) {
    
    /* Find the index of the appropriate linked-list using the first letter of the given name */
    char letter = newName[0]; int letterIndex;
    if (letter >= 65 && letter <= 90) letterIndex = (int) letter - 65;
    else if (letter >= 97 && letter <= 122) letterIndex = (int) letter - 97;
    else {printf("***ERROR: Please start names with a letter\n"); return;} 
    struct CONTACT_NODE *contact_node_i = LETTER_HEAD_CONTACT_NODES[letterIndex];

    /* Creates new contact and initialize data variables */
    struct CONTACT_NODE *newContact = (struct CONTACT_NODE *) malloc(sizeof(struct CONTACT_NODE));
    strcpy(newContact->name,newName);
    strcpy(newContact->phoneNumber,newPhoneNumber);

    /* After newName has been implemented into the newContact, set newName to uppercase (for case insentitivity) */
    int i; for (i=0;i<strlen(newName); i++) if (newName[i] >= 97 && newName[i] <= 122) newName[i] -= 32; 
    
    /* Case 1: Empty: Make the new contact the head */
    if (contact_node_i == NULL) {
        newContact->NEXT = NULL;
        newContact->PREV = NULL;
        LETTER_HEAD_CONTACT_NODES[letterIndex] = newContact; 
        return;
    }
    
    /* Starts iterating over LETTER_HEAD_CONTACT_NODES */
    char savedName[50], savedName2[50];
    while (contact_node_i != NULL) {
        
	/* Cast all character to uppercase for comparison  */
        strcpy(savedName,contact_node_i->name);
        for (i=0;i<strlen(savedName); i++) if (savedName[i] >= 97 && savedName[i] <= 122) savedName[i] -= 32;
        if (contact_node_i->NEXT != NULL) {
             strcpy(savedName2,contact_node_i->NEXT->name);
             for (i=0;i<strlen(savedName2); i++) if (savedName2[i] >= 97 && savedName2[i] <= 122) savedName2[i] -= 32;
	}
 
        /* Check for duplicate */
        if (strcmp(savedName, newName) == 0) {
            printf("***ERROR: A contact with this name already exist in the directory; please choose another name\n");
            return;
        }
        
        /* Case 2: Before Head: Make the new contact the head and place it before the former */
        if (contact_node_i->PREV == NULL && strcmp(newName, savedName)<0) {
            LETTER_HEAD_CONTACT_NODES[letterIndex] = newContact;
            newContact->PREV = NULL;
            newContact->NEXT = contact_node_i;
            contact_node_i->PREV = newContact;
            return;
        }
        
        /* Case 3: After Tail: Assign the new contact after the tail */
        else if (contact_node_i->NEXT == NULL && strcmp(newName, savedName)>0){
            newContact->PREV = contact_node_i;
            newContact->NEXT = NULL;
            contact_node_i->NEXT = newContact;
            return;
        }
        
        /* Case 4: Middle: Change adjacent nodes and insert new node between them */
        else if (strcmp(newName,savedName2)<0 && strcmp(newName, savedName)>0) {
            newContact->PREV = contact_node_i;
            newContact->NEXT = contact_node_i->NEXT;
            contact_node_i->NEXT->PREV = newContact;
            contact_node_i->NEXT = newContact;
            return;
        }
        
        /* Next iteration */
        contact_node_i = contact_node_i->NEXT;
        
    } 
}    

/* delete - indentifies the contact with the given name through iteration, use "free" to delete it, and conjoin adjacent lists */
void delete(char* oldName) {
    
    /* Find the index of the appropriate linked-list using the first letter of the given name */
    char letter = oldName[0]; int letterIndex;
    if (letter >= 65 && letter <= 90) letterIndex = (int) letter - 65;
    else if (letter >= 97 && letter <= 122) letterIndex = (int) letter - 97;
    else {printf("***ERROR: Please start names with a letter\n"); return;} 
    struct CONTACT_NODE *contact_node_i = LETTER_HEAD_CONTACT_NODES[letterIndex];
    
    /* Cast oldName to uppercase */
    int i; for (i=0;i<strlen(oldName); i++) if (oldName[i] >= 97 && oldName[i] <= 122) oldName[i] -= 32;
 
    /* Starts iterating over LETTER_HEAD_CONTACT_NODES */
    char savedName[50];
    while (contact_node_i != NULL) {
        
	    /* Case current node name to uppercase */
        strcpy(savedName, contact_node_i->name);
        for (i=0;i<strlen(savedName); i++) if (savedName[i] >= 97 && savedName[i] <= 122) savedName[i] -= 32;


        /* Check if the old name is equal to the one in the current node */
        if (strcmp(oldName, savedName)==0) {

            /* Case 1: Dead Single: Delete the head */
            if (contact_node_i->PREV == NULL && contact_node_i->NEXT == NULL) {
                free(LETTER_HEAD_CONTACT_NODES[letterIndex]);
                LETTER_HEAD_CONTACT_NODES[letterIndex] = NULL;
                return;
            }
            
            /* Case 2: Dead Head: Delete the head, and make the next node the new head */
            else if (contact_node_i->PREV == NULL) {
                free(LETTER_HEAD_CONTACT_NODES[letterIndex]);
                LETTER_HEAD_CONTACT_NODES[letterIndex] = contact_node_i->NEXT;
                return;
            }
            
            /* Case 3: Dead Tail: Delete the tail, and adjust the second-last node */
            else if (contact_node_i->NEXT == NULL) {
                free(contact_node_i);
                contact_node_i->PREV->NEXT = NULL;
                return;
            }
            
            /* Case 4: Conjoined Middle: Delete the current node and link adjacent nodes */
            else {
                free(contact_node_i);
                contact_node_i->PREV->NEXT = contact_node_i->NEXT;
                contact_node_i->NEXT->PREV = contact_node_i->PREV;
                return;
            }
            
        }
        
        /* Next iteration */
        contact_node_i = contact_node_i->NEXT;
        
    } printf("***ERROR: Contact associated with given name is not found\n");
    
}

/* reverse() - Reverse the order of all linked lists (DEFAULT: index should equal 0) */
void reverse(struct CONTACT_NODE *nodeP1, struct CONTACT_NODE *nodeP2, int index) {
    
    /* Base case: index = 26 */
    if (index == 26) return;
    
    /* Recursive Case 1: Head does not exist */
    if (LETTER_HEAD_CONTACT_NODES[index] == NULL) {return reverse(NULL, NULL, index+1);}
    
    /* Recursive Case 2: Node arguments are both NULL */
    if (nodeP1 == NULL) {
        nodeP1 = LETTER_HEAD_CONTACT_NODES[index];
        nodeP2 = LETTER_HEAD_CONTACT_NODES[index];
        while (nodeP2->NEXT != NULL) nodeP2 = nodeP2->NEXT; printf("");
        return reverse(nodeP1, nodeP2, index);
    }
    
    /* Recursive Case 3: Both are center */
    if (nodeP1 == nodeP2 || nodeP1->PREV == nodeP2) {return reverse(NULL, NULL, index+1);}
    
    /* Recursive Case 4: Both are outliers */
    if (nodeP1->PREV == NULL) {
        char tn[50], tpn[50];
        strcpy(tn, nodeP1->name);
        strcpy(tpn, nodeP1->phoneNumber);
        strcpy(LETTER_HEAD_CONTACT_NODES[index]->name, nodeP2->name);
        strcpy(LETTER_HEAD_CONTACT_NODES[index]->phoneNumber, nodeP2->phoneNumber);
        strcpy(nodeP2->name, tn);
        strcpy(nodeP2->phoneNumber, tpn);
        return reverse(LETTER_HEAD_CONTACT_NODES[index]->NEXT, nodeP2->PREV, index);
    }
    
    /* Recursive Case 5: Switch nodes and move towards center */
    else {
        char tn[50], tpn[50];
        strcpy(tn, nodeP2->name);
        strcpy(tpn, nodeP2->phoneNumber);
        strcpy(nodeP2->name, nodeP1->name);
        strcpy(nodeP2->phoneNumber, nodeP1->phoneNumber);
        strcpy(nodeP1->name, tn);
        strcpy(nodeP1->phoneNumber, tpn);
        return reverse(nodeP1->NEXT, nodeP2->PREV, index);
    }
}
