/* Mods */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Purpose of this file:
   Count the number of words in a .txt file. */

/* MAIN */
int main(int argc, char* argv[])
{
	/* Get specified file to be word-counted */
	FILE *FP = fopen(argv[1],"r");
	
	/* Scan file and count words */
	char word[200] = "";
	char setOfWord[100][200];
	int count = 0;
	int unicount = 0;
	int i,j;
	while (fscanf(FP, "%s ", word) > 0) {
		count++;
		
		i=0;
		j=0;
		for (;i<unicount;i++) 
			if (strcmp(setOfWord[i], word) == 0) {
				j++;
				break;
			}
		if (j == 0) {
			strcpy(setOfWord[i], word);
			unicount++;
		}
		 
	}

	/* Output resulting count */
	printf("%d Total Words\n", count);
	printf("%d Unique Words\n", unicount);
	
	/* Close file */
	fclose(FP);

}
	

