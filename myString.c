#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char* String;


/* initialize a given pointer to a declared char pointer
 */
String getString ()
{
  char character;
  String string = NULL;

  short i = 0;

  while (character != '\n')
  {

    // re-allocate (resize) memory for character read to be stored
    string = (char*) realloc(string, (i+1) * sizeof(char));

    // read the input from keyboard standard input
    character = getc(stdin);

    // store read character by making pointer point to c
    string[i] = character;

    i++;
  }

  // at the end append null character to mark end of string
  string[i] = '\0';

  return string;
}



/* capitalize first letter in each word of a string
 */
void initialsToUpper (String string) {

    int i;
    for (i=0 ; i<strlen(string) ; i++) {

      // capitalize lowercase alphabets if being first letter or preceded by a space
        if ( ( (i==0) || isspace(string[i-1]) ) && (string[i]>='a') && (string[i]<='z') )
            string[i]=toupper(string[i]);
    }
}