/*
 *
 * C Program To Implement Constricted Stack Using Dynamic Memory Allocation.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define true 1
#define false 0


/* expects one parameter: length of stack (array within the stack struct).
 */
Stack * constructStack (int length)
{
	// dynamically allocating memory for stack
	Stack * stack = malloc(sizeof(Stack));

	// failure check
	if(stack==NULL)
		return NULL;

	// dynamically allocating memory for elements
	stack->elements = malloc(length*sizeof(TYPE));

	// failure check
	if(stack->elements==NULL)
	{
		stack->exception = FAILED_TO_CONSTRUCT;

		// if array within the struct could not be allocated
		// deallocate stack struct
		free(stack);

		return NULL;
	}

	// if successfully allocated
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

	// deallocate
	free(stack->elements);
	free(stack);

	return NO_EXCEPETIONS;
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
	stack->elements[stack->top++]=value;

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
		return stack->exception = (TYPE) STACK_IS_EMPTY;

	// no thrown exceptions
	stack->exception = NO_EXCEPETIONS;

	// decrement top then pop
	return stack->elements[--stack->top];
}



/* expects one parameter: any given stack address.
 * functionality: returns top element value
 */
TYPE getPeekValue (Stack * stack)
{
	// avoid garbage display
	if (isEmptyStack(stack))
		return 0;

	return stack->elements[stack->top-1];
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


/* boolean check.
 * searches for a given target within a given stack.
 */
int searchStack (Stack * stack , TYPE target)
{
	// boundary variable
	int TOP = stack->top;

	// iterator
	int i = stack->top;

	// push element by element
	while( i>=1 )
		if ( target == stack->elements[TOP-(i--)] )
			return true;

	return false;
}


/* copies a stack into one another.
 */
void copyStack (Stack * stackDestination , Stack * stackSource)
{
	// boundary variable
	int TOP = stackSource->top;

	// iterator
	int i = stackSource->top;

	// push element by element
	while( i>=1 )
		push(stackDestination , stackSource->elements[TOP-(i--)] );
}


/* reverses a given stack from top to bottom.
 * returns a pointer to the same given stack.
 */
Stack * reverseStack (Stack * stack)
{
	// temporary stack to reserve sent one
	Stack * reversedStack = constructStack(stack->top);

	int TOP = stack->top;

	// iterator
	int i = 1;

	// reversing
	while ( i<=TOP )
		push(reversedStack , stack->elements[TOP-(i++)] );

    // unload sent stack to push reversed elements order
    unloadStack(stack);

    // copy reversed temporary stack to sent one
    copyStack(stack , reversedStack);

	// deallocate due function stack
	// avoid memory leakage
	destructStack(reversedStack);

	return stack;
}


/* boolean check.
 */
int isFullStack (Stack * stack)
{
	return (stack->top < stack->length) ? false : true;
}


/* boolean check.
 */
int isEmptyStack (Stack * stack)
{
	return (stack->top == 0) ? true : false;
}


/* handles exceptions that may occur in a given stack.
 */
void stackExeptionHandler (Stack * stack)
{
	switch(stack->exception)
	{
		// no thrown exceptions
		case NO_EXCEPETIONS:
			return;

		case STACK_IS_FULL:
			fprintf(stderr,"stack is full\n");
			return;

		case STACK_IS_EMPTY:
			fprintf(stderr,"stack is empty\n");
			return;

		case STACK_IS_DESTRUCTED:
			fprintf(stderr,"stack is destructed\n");
			return;
	}
}
