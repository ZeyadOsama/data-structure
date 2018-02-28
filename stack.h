#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

// to change stack type
#define TYPE int

typedef struct { } Stack;

// instantiating and destructing stack
Stack * constructStack (int size);
int destructStack (Stack * stack);

int push (Stack * stack , TYPE value);
TYPE pop (Stack * stack);

// boolean checks
int isFullStack (Stack * stack);
int isEmptyStack (Stack * stack);

void displayStack (Stack * stack);
void searchStack (Stack * stack , TYPE target);

int unloadStack (Stack * stack);

void stackExeptionHandler (Stack * stack);


#endif // STACK_H_INCLUDED
