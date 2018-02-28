/*
 *
 * C Program to Implement Constrict Stack Using Dynamic Memory Allocation
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define TYPE int
// typedef int TYPE;

#define true 1
#define false 0

enum exceptionTags
{
	NO_EXCEPETIONS,
	STACK_IS_EMPTY,
	STACK_IS_FULL,
	STACK_IS_DESTRUCTED
};


/*
 * stack data type declaration
 */
typedef struct
{
	int top;
	TYPE * items;

	// holds exception -if there is- of the stack
	int exception;

	int size;
}Stack;


/*
 * prototypes
 */
Stack * constructStack (int size);
void destructStack (Stack * stack);
int push (Stack * stack , TYPE value);
TYPE pop (Stack * stack);
int isFullStack (Stack * stack);
int isEmptyStack (Stack * stack);
void unloadStack (Stack * stack);
void displayStack (Stack * stack);
void searchStack (Stack * stack , TYPE target);
void stackExeptionHandler (Stack * stack);


Stack * constructStack (int size)
{
	// dynamically allocating memory for stack
	Stack * stack = (Stack*) malloc(sizeof(Stack));

	// failure check
	if(stack==NULL)
        return NULL;

	// dynamically allocating memory for items
	stack->items = (TYPE*) malloc(size*sizeof(TYPE));

	// failure check
	if(stack->items==NULL)
	{
		free(stack);
        return NULL;
	}

	// initializing content
	stack->top = 0;
	stack->size = size;
	stack->exception = STACK_IS_EMPTY;

	return stack;
}


void destructStackStack (Stack * stack)
{
	stack->exception = STACK_IS_DESTRUCTED;
    free(stack->items);
    free(stack);
}


int push (Stack * stack , TYPE value)
{
	// check if already full
	if(isFullStack(stack))
        return stack->exception = STACK_IS_FULL;

	// increment top then push
	stack->items[stack->top++]=value;

	return stack->exception = NO_EXCEPETIONS;
}


TYPE pop (Stack * stack)
{
	// check if already empty
	if(isEmptyStack(stack))
        return stack->exception = STACK_IS_EMPTY;

	// decrement top then pop
	return stack->items[--stack->top];
}


void unloadStack (Stack * stack)
{
	while (!isEmptyStack(stack))
		pop(stack);
}


void displayStack (Stack * stack)
{
	Stack * cop = constructStack(stack->size);

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


int isFullStack (Stack * stack)
{
	return (stack->top < stack->size) ? false : true;
}


int isEmptyStack (Stack * stack)
{
	return (stack->top==0) ? true : false;
}


/*
void searchStack (Stack * stack , TYPE target)
{
	int i,j;

	for (i=0; i<stack->top ; i++)
	{
		for (j=0; j<i ; j++)
		{

		}
	}
}
*/


/*
 * handles exceptions that may occur in a given stack
 */
void stackExeptionHandler (Stack * stack)
{
	switch(stack->exception)
	{
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