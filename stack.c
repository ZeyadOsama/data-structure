/*
 *
 * C Program to Implement Constrict Stack Using Dynamic Memory Allocation
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define TYPE int

#define true 1
#define false 0


/* defining enumeration for exceptions tags
 */
typedef enum
{
	NO_EXCEPETIONS ,
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
	TYPE * items;

	// holds exception -if there- for a given stack
	int exception;
} Stack;


/* prototypes
 */
Stack * constructStack (int length);
int destructStack (Stack*);
int push (Stack* , TYPE value);
TYPE pop (Stack*);
int isFullStack (Stack*);
int isEmptyStack (Stack*);
void displayStack (Stack*);
void searchStack (Stack* , TYPE target);
int unloadStack (Stack*);
void stackExeptionHandler (Stack*);


/* expects one parameter: length of stack (array within the stack struct).
 */
Stack * constructStack (int length)
{
	// dynamically allocating memory for stack
	Stack * stack = (Stack*) malloc(sizeof(Stack));

	// failure check
	if(stack==NULL)
        return NULL;

	// dynamically allocating memory for items
	stack->items = (TYPE*) malloc(length*sizeof(TYPE));

	// failure check
	if(stack->items==NULL)
	{
		// freeing stack struct if array within the struct could not be allocated
		free(stack);
        return NULL;
	}

	// initializing stack content
	stack->top = 0;
	stack->length = length;
	stack->exception = STACK_IS_EMPTY;

	return stack;
}


/* expects one parameter: any given stack address.
 */
int destructStack (Stack * stack)
{
	stack->exception = STACK_IS_DESTRUCTED;
    free(stack->items);
    free(stack);

	return STACK_IS_DESTRUCTED;
}


/* expects two parameter: any given stack address / to be inserted data.
 * functionality: add data to top of stack.
 */
int push (Stack * stack , TYPE value)
{
	// check first if already full
	if(isFullStack(stack))
        return stack->exception = STACK_IS_FULL;

	// increment top then push
	stack->items[stack->top++]=value;

	// no thrown exceptions
	return stack->exception = NO_EXCEPETIONS;
}


/* expects one parameter: any given stack address.
 * functionality: remove data from top of stack.
 * could be assigned to variables.
 */
TYPE pop (Stack * stack)
{
	// check first if already empty
	if(isEmptyStack(stack))
        return stack->exception = STACK_IS_EMPTY;

    // no thrown exceptions
    stack->exception = NO_EXCEPETIONS;

	// decrement top then pop
	return stack->items[--stack->top];
}


/* expects one parameter: any given stack address.
 * functionality: remove all content of a given stack
 */
int unloadStack (Stack * stack)
{
	while (!isEmptyStack(stack))
		pop(stack);

	// throw exception to assure no popping
	return stack->exception = STACK_IS_EMPTY;
}


void displayStack (Stack * stack)
{
	Stack * cop = constructStack(stack->length);

	printf("[ ");

	while (!isEmptyStack(stack))
	{
		TYPE temp = pop(stack);
		printf("%i ",temp);
		push(cop,temp);
	}

	printf("]\n");

	while (!isEmptyStack(cop)) {
		push(stack,pop(cop));
	}
}


/* boolean check
 */
int isFullStack (Stack * stack)
{
	return (stack->top < stack->length) ? false : true;
}


/* boolean check
 */
int isEmptyStack (Stack * stack)
{
	return (stack->top == 0) ? true : false;
}


/*
void searchStack (Stack * stack , TYPE target)
{
	int i,j;

	for (i=0; i<stack->top ; i++)
	{
		for (j=0; j<i ; j++)
		{
			// TO DO CODE HERE
		}
	}
}
*/


/* expects one parameter: any given stack address.
 * functionality: handles exceptions that may occur in a given stack
 */
void stackExeptionHandler (Stack * stack)
{
	switch(stack->exception)
	{
		// no thrown exceptions
		case NO_EXCEPETIONS:
			break;

		case STACK_IS_FULL:
			fprintf(stderr,"stack is full\n");
			break;

		case STACK_IS_EMPTY:
			fprintf(stderr,"stack is empty\n");
			break;

		case STACK_IS_DESTRUCTED:
			fprintf(stderr,"stack is destructed\n");
			break;
	}
}
