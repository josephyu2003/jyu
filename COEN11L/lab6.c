/* Mods */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* CONTACT_NODE - represents a single contact */
struct CONTACT_NODE {
    char name[20];   // the name of person associated
    char phoneNumber[20];   // the phone number of person associated
    struct CONTACT_NODE *NEXT;   // the pointer to the next array
};


/* HEAD_CONTACT_NODE - represents the head of the contact data structure */
struct CONTACT_NODE *LETTER_HEAD_CONTACT_NODES[26];

/* Functions List */
int insert(char newName[20], char newPhoneNumber[20]);
int delete(char oldName[20]);
void show();
void show_letter(char letter);

/* MAIN */
int main() {
    
    /* Begins the program with an introduction and lists out all of the possible commands */
	char *openingMessage = "\n"
		"#=====================================#\n"
		"| PHONE BOOK 4.0 (NOW WITH LETTERING) |\n"
		"#=====================================#\n"
		"1 -> Create a new contact for the directory\n"
		"2 -> Delete a contact off of the directory\n"
                "3 -> Show all known contacts in the directory\n"
                "4 -> Show all known contacts that start with a specified letter\n"
                "5 -> Quits the program\n"
                "NOTE: Please start names with letter\n\n";
    printf("%s", openingMessage);   // print the opening message
    
    /* the titles to the contact listing */
    char *contactListTitle = 
        "#==================#\n"
	"| LIST OF CONTACTS |\n"
	"#==================#\n";
	char contactListTitle2[92] = 
        "#====================#\n"
	"| LIST OF CONTACTS 0 |\n"
	"#====================#\n";
	
	/* Initialize LETTER_HEAD_CONTACT_NODES */ 
	/* Note-to-self: actualHEADS is created so that the linked-list heads don't point to the same variable*/
	int i;
	for (i=0;i<26;i++) {              
	    LETTER_HEAD_CONTACT_NODES[i] = NULL;
	}
	
	/* Initialize temporary game values */
        srand((int) time (NULL));  // Set up the Scanner
        int callNumber; char phoneNumber[20], name[20], letterMSG[20], letter;
    
        /* Start game loop */
	for (;;) {
	    
	    /* Get user input */
	    printf(">>> ");
	    scanf("%d", &callNumber);
	
	    /* Parse input */
	    switch (callNumber) {
	        
	        /* '5' - quits program */
	        case 5:
	            printf("Thank you for using PHONE BOOK 4.0\n"); // goodbye message
	            return 0; // kills program
	            
	        /* '4' - displays contacts with names starting with a certain letter */
	        case 4:
	        
	            /* Scan for letter */
	            printf("Enter a Letter: "); scanf("%s", letterMSG);  letter = letterMSG[0]; 
	            
	            /* Check if letter is valid and plug it into listing title */
	            if (letter >= 65 && letter <= 90) {
	                contactListTitle2[42] = letter;
	            }
	            else if (letter >= 97 && letter <= 122) {
	                contactListTitle2[42] = letter-32;
	            }
	            else break;
	            
	            /* Show contact list with given letter */
	            if (strlen(letterMSG)==1) {
	                printf("%s",contactListTitle2);
	                show_letter(contactListTitle2[42]);    // contactListTitle2[42] = uppercase letter
	            } else printf("***ERROR***: Please type a valid letter.\n"); 
	            break;   // next iteration
	        
	        /* '3' - displays all contacts in a table */
	        case 3:
	            printf("%s", contactListTitle);   // introduce the contact list page
	            show();  // show the contacts
	            break;   // next iteration
	            
	        /* '2' - delete a contact from the linked list */
	        case 2:
	            printf("Name (for Deletion): "); scanf("%s", name);   // scan for the name for deletion
                    if (!delete(name)) {printf("***ERROR***: Name unfound in linked list; please check for typos.\n");}   // Delete contact
	            break;   // next iteration
	            
	        /* '1' - add a new contact node into the linked list */
	        case 1:
	            printf("Name: "); scanf("%s", name);   // Scan for name
	            printf("Phone Number: "); scanf("%s", phoneNumber);   // Scan for phoneNumber
	            if (!insert(name, phoneNumber)) {printf("***ERROR***: Invalid name; check for duplicate or please start name with a letter \n");} 
	            break; // next iteration
	    
	        /* In all other cases, (ideally) do nothing */
	        default:
	            printf("***ERROR***: Invalid command. Please re-read instructions and check for typos.\n"); 
	            break;
	            
	   }
	}
}

/* insert - given the name and phone number, creates a new contact, checks for duplicates, and 
            then inserts a new contact into the correct alphabetical position */
int insert(char newName[20], char newPhoneNumber[20]) {
    
    /* First, find which linked-list should be refered to in the array */
    char letter = newName[0]; int letterIndex;
    if (letter >= 65 && letter <= 90) letterIndex = (int) letter - 65;
    else if (letter >= 97 && letter <= 122) letterIndex = (int) letter - 97;
    else return 0;

    /* set up variables to iterate through linked list */
    struct CONTACT_NODE *contact_node_i = LETTER_HEAD_CONTACT_NODES[letterIndex]; 
    struct CONTACT_NODE *prev_contact_node_i = NULL;
    
    /* define new structure to represent the new contact */
    struct CONTACT_NODE *newContact;
    newContact = (struct CONTACT_NODE*) malloc(sizeof(struct CONTACT_NODE));
    strcpy(newContact->name, newName);
    strcpy(newContact->phoneNumber, newPhoneNumber);

    /* if HEAD_CONTACT_NODE doesn't exist, then assign the new contact to it, and assign the next contact to NULL */
    if (LETTER_HEAD_CONTACT_NODE[letterIndex] == NULL) {
        newContact->NEXT = NULL;
        LETTER_HEAD_CONTACT_NODE[letterIndex] = newContact;
        return 1;   // exit function with no error
    }

    // Used for a later for loop to avoid segmentation fault
    int smallerNameLength, ishead=1, abcVS;

    /* Otherwise, loop over linked list (to find proper "next" value) */
    /* while the current contact node in iteration */
    while (contact_node_i != NULL) {

        /* Evaluate in case of duplicate; if duplicate is found, return error */
        /* Otherwise, check alphabtical placement using strcmp (as suggested by TAs) */
        if (strcmp(newContact->name, contact_node_i->name)==0) return 0;
        if (strcmp(newContact->name, contact_node_i->name)<0) abcVS = 0;
        if (strcmp(newContact->name, contact_node_i->name)>0) abcVS = 1;
        
        
        /* if abcVS = 0 and the iterator is currently on the head, reset the head */
        if (abcVS == 0 && ishead) {
            newContact->NEXT = contact_node_i;
            HEAD_CONTACT_NODE = newContact;
            return 1;
        }
        
        /* if abcVS = 1, */
        else if (abcVS == 1) {
            /* if on head node, just link the head to the new node as the second one */
            if (ishead) {
                if (contact_node_i->NEXT != NULL && strcmp(newContact->name, contact_node_i->NEXT->name)>0){
                    prev_contact_node_i = contact_node_i;
                    contact_node_i = contact_node_i->NEXT;
                    ishead = 0;                     
                     continue;
                } // (abuse short circuit here)
                   
                else {
                    newContact->NEXT = contact_node_i->NEXT;
                    contact_node_i->NEXT = newContact;
                    return 1;
                }
            }
            /* if abc = 1 and on tail, simply attatch newContact to the end of the list */
            if (contact_node_i->NEXT == NULL) {
                contact_node_i->NEXT = newContact;
                newContact->NEXT = NULL;
                return 1;
            }
            /* if not isHead, the contact belongs in the place BEHIND that node */
            /* thus, link the previous node to the new one, and link the new one to the iterated */
            prev_contact_node_i->NEXT = newContact;
            newContact->NEXT = contact_node_i;
            return 1;
        }
        
        /* In other cases, simply move on to the next linked list */
        prev_contact_node_i = contact_node_i;
        contact_node_i = contact_node_i->NEXT;
        ishead = 0;
        
    }
}

/* delete - given the name, checks to see if the contact associated with the name exists, 
            frees a contact node , and links adjacent values*/
int delete(char oldName[20]) {

    /* First, find which linked-list should be refered to in the array */
    char letter = oldName[0]; int letterIndex;
    if (letter >= 65 && letter <= 90) letterIndex = (int) letter - 65;
    else if (letter >= 97 && letter <= 122) letterIndex = (int) letter - 97;
    else return 0;
    
    /* set up variable to iterate through linked list */
    struct CONTACT_NODE *contact_node_i = HEAD_CONTACT_NODE, *prev_contact_node_i = NULL;
    
    /* Check the head first */
    if (contact_node_i != NULL && strcmp(oldName, contact_node_i->name)==0) { // again, abuse short circuit
        HEAD_CONTACT_NODE = contact_node_i->NEXT;  // makes the next node the new head
        free(contact_node_i);   // frees the original head
        return 1;
    }
    
    /* Otherwise, loop over linked list (to find the name rigged for deletion) */
    while (contact_node_i != NULL) {
        
        /* Checks to see if the current node has the given name set for deletion */
        if (strcmp(oldName, contact_node_i->name)==0) {
            // Check to see if it is a tail node
            if (contact_node_i->NEXT == NULL) {
                prev_contact_node_i->NEXT = NULL;  // make the second-last the new tail
                free(contact_node_i);   // free the tail
                return 1;
            }
            // otherwise, just free the given node, and conjoin the adjacent nodes
            prev_contact_node_i->NEXT = contact_node_i->NEXT;
            free(contact_node_i); 
            return 1;
        }
        
        /* In other cases, simply move on to the next linked list */
        prev_contact_node_i = contact_node_i;
        contact_node_i = contact_node_i->NEXT;
        
    } return 0;
}
   

/* show - display all known contacts from every linked-List in a table */
void show() {
    
    /* start iterating over list */
    struct CONTACT_NODE *contact_node_i; int i;
    for (i=0;i<26;i++) {
      contact_node_i = LETTER_HEAD_CONTACT_NODES[i];
        while (contact_node_i != NULL) {
            printf("%s : %s\n", contact_node_i->name, contact_node_i->phoneNumber);
            contact_node_i = contact_node_i->NEXT;
        }
    } printf("\n"); return;
    
}

/* show_letter - display contacts of a specified letter in a table */
void show_letter(char letter) {
    struct CONTACT_NODE *contact_node_i = LETTER_HEAD_CONTACT_NODES[((int) letter)-65];
    while (contact_node_i != NULL) {
            printf("%s : %s\n", contact_node_i->name, contact_node_i->phoneNumber);
            contact_node_i = contact_node_i->NEXT;
    }
}





