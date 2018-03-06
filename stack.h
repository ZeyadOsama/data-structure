#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

// to change stack type
#define TYPE int


/* defining enumeration for exceptions tags
 */
typedef enum
{
	NO_EXCEPETIONS ,
	FAILED_TO_CONSTRUCT ,
	STACK_IS_EMPTY ,
	STACK_IS_FULL ,
	STACK_IS_DESTRUCTED
} ExceptionTags;


/* stack data-type declaration
 */
typedef struct
{
	int top;
	int length;

	// pointer to array of a given data-type
	// to be dynamically allocated by length through run-time
	TYPE * elements;

	// holds exception -if there- for a given stack
	int exception;
} Stack;


// instantiating and destructing stack
Stack * constructStack (int size);
int destructStack (Stack * stack);

int push (Stack * stack , TYPE value);
TYPE pop (Stack * stack);

TYPE getPeekValue (Stack * stack);

// boolean checks
int isFullStack (Stack * stack);
int isEmptyStack (Stack * stack);
int searchStack (Stack * stack , TYPE target);


// utility functions
void displayStack (Stack * stack);
void copyStack (Stack * stackDestination , Stack * stackSource);
Stack * reverseStack (Stack * stack);

int unloadStack (Stack * stack);

void stackExeptionHandler (Stack * stack);


#endif // STACK_H_INCLUDED
