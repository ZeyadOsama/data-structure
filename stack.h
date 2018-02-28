#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdbool.h>

#define TYPE int

typedef struct
{

}Stack;

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


#endif // STACK_H_INCLUDED
