/* Mods */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*

Phone Book 4.0:
Keeps a list of contacts in a data structure, from which contacts can be added, deleted, and displayed.

Commands:
1 -> Add a new record into the directory after entering the name, age, and status
2 -> Take a contact off of the directory after calling the name associated with the record
3 -> Show all known contacts
4 -> Show all known contacts with names starting with a specified letter.
5 -> Close the program

Requirements:
- One global array of linked-list heads of size 26 (done)
- Five functions: main, insert, delete, show, show_letter 
- Functions other than main are declared before main and defined after main (done)
- No other global variables/functions other than the ones listed above (done)
- Head nodes' NEXT variable is set to NULL upon intialization 
- Linked-list heads point to separate linked-lists that represent letters of the alphabet
- The individual linked-lists are alphabetically sorted using strcmp(string1,string2) 
- Each linked-list node had a name, a phone number, and a pointer to the next node (done)
- Use doubly-linked lists for bonus credit
- The program works as intended

*/

/* CONTACT_NODE - represents a single contact */
struct CONTACT_NODE {
    char name[20];   // the name of person associated
    char phoneNumber[20];   // the phone number of person associated
    struct CONTACT_NODE *NEXT;   // the pointer to the next array
    struct CONTACT_NODE *PREV;   // the pointer to the prev array
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
	            printf("Thank you for using PHONE BOOK 3.0\n"); // goodbye message
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

/* insert() - inserts a contact into one of the linked-lists, based on the first letter of the name */
int insert(char newName[20], char newPhoneNumber[20]) {
    
    /* First, find which linked-list should be refered to in the array */
    char letter = newName[0]; int letterIndex;
    if (letter >= 65 && letter <= 90) letterIndex = (int) letter - 65;
    else if (letter >= 97 && letter <= 122) letterIndex = (int) letter - 97;
    else return 0;
    
    /* define new structure to represent the new contact */
    struct CONTACT_NODE *newContact;
    newContact = (struct CONTACT_NODE*) malloc(sizeof(struct CONTACT_NODE));
    strcpy(newContact->name, newName);
    strcpy(newContact->phoneNumber, newPhoneNumber);
    
    /* start iterating over list*/
    struct CONTACT_NODE *contact_node_i = LETTER_HEAD_CONTACT_NODES[letterIndex];
    if (LETTER_HEAD_CONTACT_NODES[letterIndex] == NULL) {
         newContact->NEXT = NULL;
         newContact->PREV = NULL;
         LETTER_HEAD_CONTACT_NODES[letterIndex] = newContact; return 1;
    }
    while (contact_node_i != NULL) {
        
        // Check if duplicate is found; if found, exit immediately
        if (strcmp(contact_node_i->name, newName) == 0) return 0;
        
        // Case 1: Head
        else if (contact_node_i->PREV == NULL && strcmp(newName, contact_node_i->name)<0) {
            newContact->PREV = NULL;
            newContact->NEXT = contact_node_i;
            contact_node_i->PREV = newContact;
            LETTER_HEAD_CONTACT_NODES[letterIndex] = newContact;
            return 1;
        }
            
        // Case 2: Tail
        else if (contact_node_i->NEXT == NULL && strcmp(newName, contact_node_i->name)>0) {
            newContact->NEXT = NULL;
            newContact->PREV = contact_node_i;
            contact_node_i->NEXT = newContact;
            return 1;
        }
            
        // Case 3: Middle (if the next name > new name and the current name < new name)
        else if (strcmp(newName, contact_node_i->NEXT->name)<0 && strcmp(newName, contact_node_i->name)>0){
            contact_node_i->NEXT->PREV = newContact;
            newContact->NEXT = contact_node_i->NEXT;
            contact_node_i->NEXT = newContact;
            newContact->PREV = contact_node_i;
            return 1;
        }
        
        // Next iteration
        else contact_node_i = contact_node_i->NEXT;
    } return 0;
    
}

/* delete - remove a contact from the appropriate linked-list and link adjacent lists */
int delete(char oldName[20]) {
    
    /* First, find which linked-list should be refered to in the array */
    char letter = oldName[0]; int letterIndex;
    if (letter >= 65 && letter <= 90) letterIndex = (int) letter - 65;
    else if (letter >= 97 && letter <= 122) letterIndex = (int) letter - 97;
    else return 0; 
    
    /* start iterating over list */
    struct CONTACT_NODE *contact_node_i = LETTER_HEAD_CONTACT_NODES[letterIndex];
    while (contact_node_i != NULL) {
        
        // Find if current node has the given name
        if (strcmp(oldName, contact_node_i->name) == 0)  {

	     // Case 1: Head
	     if (contact_node_i->PREV = NULL) {
	          if (contact_node_i->NEXT = NULL) {
		       LETTER_HEAD_CONTACT_NODES[letterIndex] = NULL;
                  } else {
                       LETTER_HEAD_CONTACT_NODES[letterIndex] = contact_node_i->NEXT;
                       LETTER_HEAD_CONTACT_NODES[letterIndex]->PREV = NULL;                      
 		  }
             }

             // Case 2: Tail
             else if (contact_node_i->NEXT = NULL) {
                  contact_node_i->PREV->NEXT = NULL;          
             }

             // Case 3: Middle
             else {
                  contact_node_i->NEXT->PREV = contact_node_i->PREV;
                  contact_node_i->PREV->NEXT = contact_node_i->NEXT;
             }

	     free(contact_node_i);
	     return 1; */
        }
	
	// Next iteration
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
