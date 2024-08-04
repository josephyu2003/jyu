/* Mods */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "lab9.h"

/* main.c - contains the function main() and is the centric file of the project */

/*

Phone Book 7.0:
A directory program in which the computer allows the user to add, delete, or display contacts.

Commands:
1 - Adds a new contact to the directory
2 - Delete an old contact from the directory
3 - Show a table of all contacts
4 - Show a table of all contacts with names of a specified starting letter
5 - Record directory contents into a binary file
6 - Show a table of the binary file contents in readable text
7 --- 3 things:
 - Reverses the order of the contacts in the directory
 - Show the reversed directory contents
 - Reverses the order of the contacts in the directory a second time
8 - Quit and save directory to file

Requirements (to add on top of PHONEBOOK 5.0):
> Split the program into three .c files, namely "main.c," "list.c," and "files.c"
> Create a header file that just contains the global variables named "main.h"
> Include "main.h" in the project files other than main
> Create a make program to assist with compilation
> Create function "reverse()" to reverse the function
  > The function must use recursion
> The program works as intended

*/

/* MAIN */
int main(int argc, char* argv[]) {
    
    /* Create Directory and Recall FILEs, if nonexistent */
    FILE *DIRECTORY = fopen(argv[1], "a");
    FILE *BINARYRCL = fopen(argv[2], "ab");

    /* Introduces the user to the program and lists out the possible commands */
    char openingMessage[700] = "\n"
	"#===============================#\n"
	"| PHONE BOOK 7.0 (NOW WITH REV) |\n"
	"#===============================#\n"
	"1 -> Create a new contact for the directory\n"
	"2 -> Delete a contact off of the directory\n"
    "3 -> Show all known contacts in the directory in alphabetical order\n"
    "4 -> Show all known contacts that start with a specified letter\n"
    "5 -> Stores current directory in a separate file\n"
    "6 -> Recalls the stored directory from the separate file\n"
    "7 -> Show all known contacts in the directory in reverse alphabetical order\n"
    "8 -> Quits the program and saves to file\n"
    "NOTE: Please start names with letter and keep all inputs under 50 words\n\n";
    printf("%s", openingMessage); 
    
    /* Set up the titles used to introduce tables */
    char contactListTitle[100] = 
    "#==================#\n"
    "| LIST OF CONTACTS |\n"
    "#==================#\n";
    char contactListTitle2[100] = 
    "#====================#\n"
    "| LIST OF CONTACTS 0 |\n"
    "#====================#\n";
    char contactListTitle3[150] = 
    "#======================#\n"
    "| LIST OF CONTACTS RCL |\n"
    "#======================#\n"; 
    char contactListTitle4[150] =
    "#======================#\n"
    "| LIST OF CONTACTS REV |\n"
    "#======================#\n"; 
	
	/* Initialize LETTER_HEAD_CONTACT_NODES */ 
	int i; for (i=0;i<26;i++) LETTER_HEAD_CONTACT_NODES[i] = NULL;
	read_textfile(argv[1]);
	
	/* Define parsing variables*/
	char callNumber, callNumberMSG[50], phoneNumber[50], name[50], letterMSG[50], letter;
	
	/* Start Game Loop */
	for (;;) {
	    
	    /* Get user input */
	    // NOTE: fgets also copies returns so the string length of a single inputedcharacter = 2
	    printf(">>> "); fgets(callNumberMSG ,sizeof(callNumberMSG), stdin);
	    if (strlen(callNumberMSG)==2) callNumber = callNumberMSG[0]; 
	    else {printf("***ERROR: Please enter a single character.\n"); continue;}
	    
	    /* Parse user input */
	    switch(callNumber) {
	        
	        /* 1 - adds a new contact to the directory*/
	        case '1':
	        
	            /* Get new contact information from user */
	            printf("Name: "); fgets(name, sizeof(name), stdin); name[strlen(name)-1] = '\0';
	            printf("Phone Number: "); fgets(phoneNumber, sizeof(name), stdin);  phoneNumber[strlen(phoneNumber)-1] = '\0';
	            
	            /* Creates new contact and inserts said contact into directory*/
	            insert(name, phoneNumber); break;
	        
	        /* 2 - subtract a contact from the directory */
	        case '2':
	        
	            /* Get name for deletion */
	            printf("Name (for deletion): "); fgets(name, sizeof(name), stdin); name[strlen(name)-1] = '\0';
	            
	            /* Delete contact associated with name off the directory */
	            delete(name); break;
	        
	        /* 3 - show all contacts */
	        case '3':
	        
	            /* Print introduction message and tabuluated contacts */
	            printf("%s", contactListTitle);
	            show(); break;
	        
	        /* 4 - show all contacts starting with a specific letter */
	        case '4':
	        
	            /* Get letter from the user */
	            printf("Enter a Letter: "); fgets(letterMSG, sizeof(name), stdin); letter = letterMSG[0]; 

	            /* Parse letter here and change introduction message */
	            if (letter >= 97 && letter <= 122) letter -= 32;
	            else if (letter < 65 || letter > 90)  {printf("***ERROR: Please type a alphabetical letter\n"); break;}
	            contactListTitle2[42] = letter;
	            
	            /* print introduction message and tabuluated contacts */
	            if (strlen(letterMSG) == 2) {
	                printf("%s", contactListTitle2);
	                show_letter(letter); 
	            } else printf("***ERROR: Please type a alphabetical letter\n"); 
	            break;
	   
	   	/* 5 - Save current directory to binary file */
	   	case '5':
	   	    printf("Saving to RCL (binary file)...\n");
	   	    write_binaryfile(argv[2]);
	   	    break;
	   	   
	  	/* 6 - Show binary file contents */
	  	case '6':
	  	    printf("%s", contactListTitle3);
	  	    print_binaryfile(argv[2]);
	  	    break;
	  	    
	  	/* 7 - Show all contacts in reverse order and retrieve the original list after you're done*/
	  	case '7':
	  	    /* Print introduction message and tabuluated contacts */
	        printf("%s", contactListTitle4);
	        reverse(NULL, NULL, 0);
	        show(); 
	        reverse(NULL, NULL, 0);
	        break;

	    /* 8 - save the directory to file and quits */
	    case '8':
	        printf("Thank you for using PHONE BOOK 7.0.\n");
	        save_textfile(argv[1]); write_binaryfile(argv[2]); 
	        fclose(DIRECTORY); fclose(BINARYRCL); 
	        return 0;
	            
	    /* End of switch statement */
	    default: 
	        printf("***ERROR: Please type a valid command.\n");
	            
	    }
	} 
}




