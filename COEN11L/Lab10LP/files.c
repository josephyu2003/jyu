/* Mods */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include "lab10.h"

/* files.c - files for functions that writes and recalls data from .txt and .bin files */

/* read_textfile() - creates and writes nodes of the linked-lists based on the names and phone numbers written on the text file */
void read_textfile(char filename[50]) {
    
    /* Refer to contactData.txt */
    FILE *DFP = fopen(filename,"r"); 
    
    /* Find the number of characters in the file; if it doesn't have more than 201 chars, escape this function */
    /* NOTE: 202 chars is the string length of the intro */
    fseek(DFP, 0, SEEK_END); int lengthOfFile = (int) ftell(DFP);
    if (lengthOfFile<201+1) return;
    
    /* Create variables for iteration and move in-front of introduction */
    fseek(DFP, 202, SEEK_SET); 
    char name[50], phoneNumber[50], test[3];
    
    /* Start parsing text from contactData.txt */
    while (getc(DFP) != EOF) {
        
        /* Get strings of 50 chars */
        fseek(DFP, -1, SEEK_CUR);
        fgets(name, 50+1, DFP); 
        fgets(phoneNumber, 50, DFP);
        
        /* Trim the ending spaces because they are annoying */
        int i; 
        for (i=strlen(name)-1; i>=0; i--){
            if (name[i] == ' ') name[i] = '\0';
            else if (name[i] == '\0') continue;
            else break;
        } 
        for (i=strlen(phoneNumber)-1; i>=0; i--){
            if (phoneNumber[i] == ' ') phoneNumber[i] = '\0';
            else if (phoneNumber[i] == '\0') continue;
            else break;
        }
        
        /* Adjust DFP position over newline and insert reminiscent contact*/
        fseek(DFP, 2, SEEK_CUR);
        insert(name, phoneNumber);
        
    } 
    
    /* Close FILE */
    fclose(DFP); return;
    
}

/* save_textfile() - prints the names and phone numbers from the linked-list nodes onto the text file */
void save_textfile(char filename[50]) {
    
    /* Refer to contactData.txt */
    FILE *DFP = fopen(filename,"w");
    
    /* Write the beginning of the file */
    char *fileIntro = "Names                                             Number                                            \n"
                      "----------------------------------------------------------------------------------------------------\n";
    fprintf(DFP, fileIntro, "%s");
    
    /* Start iterating over lists */
    struct CONTACT_NODE *contact_node_i; int i, j; 
    for (i=0; i<26; i++) {
        contact_node_i = LETTER_HEAD_CONTACT_NODES[i];
        while (contact_node_i != NULL) {
            
            /* Explaination: 
               1) print name
               2) print (50 - length of String name) spaces 
               3) repeat step 1-2 with phoneNumber
               4) print newline */
            fprintf(DFP, "%s", contact_node_i->name);
            for (j=0; j<(50-strlen(contact_node_i->name)); j++) fprintf(DFP, " ");
            fprintf(DFP, "%s", contact_node_i->phoneNumber);
            for (j=0; j<(50-strlen(contact_node_i->phoneNumber)); j++) fprintf(DFP, " ");
            fprintf(DFP, "\n");
            
            /* Next Iteration */
            contact_node_i = contact_node_i->NEXT;
            
        }
    }
    
    /* Close FILE */
    fclose(DFP); return;
    
}

/* write_binaryfile - writes the current linked-list nodes into a binary file */
void write_binaryfile(char filename[50]) {

    /* Refer to contactBinData.txt */
    FILE *DFP = fopen(filename,"wb");
    
    /* Start iterating over lists */
    struct CONTACT_NODE *contact_node_i; int i;
    for (i=0;i<26;i++) {
	    contact_node_i = LETTER_HEAD_CONTACT_NODES[i];
        while (contact_node_i != NULL) {
	     fwrite(contact_node_i, sizeof(struct CONTACT_NODE), 1, DFP);
             contact_node_i = contact_node_i->NEXT;
	    }
    }

    /* Close FILE */
    fclose(DFP); return;

}

/* print_binaryfile - retrieves the data from the binary file and displays it into a table */
void print_binaryfile(char filename[50]) {

    /* Refer to contactBinData.txt */
    FILE *DFP = fopen(filename,"rb");
   
    /* Start iterating over file contents */
    struct CONTACT_NODE *contact_node_i= (struct CONTACT_NODE*) malloc(sizeof(struct CONTACT_NODE));  
    while (fread(contact_node_i, sizeof(struct CONTACT_NODE), 1, DFP) == 1) {
         printf("%s : %s\n", contact_node_i->name, contact_node_i->phoneNumber);
    } printf("\n");

    /* Close FILE */
    fclose(DFP); return;

}

/* show - Iterates over each contact of the linked-lists in LETTER_HEAD_CONTACT_NODES to print their information */
void show() {
    
    /* Start iterating over LETTER_HEAD_CONTACT_NODES */
    struct CONTACT_NODE *contact_node_i; int i; 
    for (i=0;i<26;i++) {
        
        /* Loop over linked-lists */
        contact_node_i = LETTER_HEAD_CONTACT_NODES[i];
        while (contact_node_i != NULL) {
            printf("%s : %s\n", contact_node_i->name, contact_node_i->phoneNumber);
            contact_node_i = contact_node_i->NEXT;
        }
    
    /* Exit function */    
    } printf("\n"); return;
    
}

/* show_letter - Identifies the index of LETTER_HEAD_CONTACT_NODES associated with the alphabet letter and only iterates over contacts
*                associated with that index/letter */
void show_letter(char letter) {
    
    /* Assign the iterative contact to the appropriate index of LETTER_HEAD_CONTACT_NODES, based on the letter */
    struct CONTACT_NODE *contact_node_i = LETTER_HEAD_CONTACT_NODES[letter-65]; 
    
    /* Start iterating over lists */
    while (contact_node_i != NULL) {
        printf("%s : %s\n", contact_node_i->name, contact_node_i->phoneNumber);
        contact_node_i = contact_node_i->NEXT;
        
    /* Exit Function */
    } printf("\n"); return;
    
}


void * autosaveToBin(void * filename){
    struct CONTACT_NODE *contact_node_i; int i;
    for (;;) {
        pthread_mutex_lock(&autosave_mutex);
        FILE * DFP = fopen( (char *) filename, "wb");
        for (i=0;i<26;i++) {
	     contact_node_i = LETTER_HEAD_CONTACT_NODES[i];
             while (contact_node_i != NULL) {
	          fwrite(contact_node_i, sizeof(struct CONTACT_NODE), 1, DFP);
                  contact_node_i = contact_node_i->NEXT;
	     }
        }
        fclose(DFP);
        pthread_mutex_unlock(&autosave_mutex);
        sleep(5);
    }      
}
