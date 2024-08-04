#ifndef lab9
#define lab9

/* Base File - contains all global variables, function declarations, and structure definitions */

/* CONTACT_NODE - a node containing the contact information */ 
struct CONTACT_NODE {
    char name[50];
    char phoneNumber[50];
    struct CONTACT_NODE *PREV;
    struct CONTACT_NODE *NEXT;
};

/* LETTER_HEAD_CONTACT_NODES - an array in which each head index represents an alphabetical letter*/
struct CONTACT_NODE *LETTER_HEAD_CONTACT_NODES[26];

/* Functions list */
void insert(char newName[50], char newPhoneNumber[50]);
void delete(char oldName[50]);
void show();
void show_letter(char letter);
void save_textfile(char filename[50]);
void read_textfile(char filename[50]);
void write_binaryfile(char filename[50]);
void print_binaryfile(char filename[50]);
void reverse(struct CONTACT_NODE *nodeP1, struct CONTACT_NODE *nodeP2, int index);

#endif
