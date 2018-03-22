#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <stdbool.h>

/* for changing linkedList type easily
 */ 
#define TYPE int


/* defining enumeration for exceptions tags
 */
typedef enum
{
	NO_LINKEDLIST_EXCEPETIONS ,
	FAILED_TO_CONSTRUCT ,
	LINKEDLIST_IS_EMPTY ,
	LINKEDLIST_IS_DESTRUCTED ,
	RANGE_OUT_OF_BOUNDS
} LinkedListExceptionTags;


/* node data-type declaration
 */
typedef struct node
{
	TYPE value;

	struct node * next;
} Node;


/* linkedList data-type declaration
 */
typedef struct
{
	Node * head;
	Node * tail;

	int length;

	// holds exception -if there- for a given linkedList
	int exception;
} LinkedList;


/* nodes functions
 */
Node * newNode (TYPE value);


/* instantiating and destructing linkedList
 */
LinkedList * constructLinkedList ();
int destructLinkedList (LinkedList * linkedList);


/* main functions for linkedLists
 */
int insertToHead (LinkedList * linkedList , TYPE value);
int insertToTail (LinkedList * linkedList , TYPE value);
int insertToIndex (LinkedList * linkedList , TYPE value , int index);

int removeFromHead (LinkedList * linkedList);
int removeFromTail (LinkedList * linkedList);
int removeFromIndex (LinkedList * linkedList , int index);

TYPE getValueOf (LinkedList * linkedList , int index);


/* boolean checks functions
 */
bool isEmptyLinkedList (LinkedList * linkedList);
Node * searchLinkedList (LinkedList * linkedList , TYPE target);


/* various utility functions
 */
int unloadLinkedList (LinkedList * linkedList);
void displayLinkedList (LinkedList * linkedList);
void copyLinkedList (LinkedList * linkedListDestination , LinkedList * linkedListSource);
LinkedList * reverseLinkedList (LinkedList * linkedList);
LinkedList * sortLinkedList (LinkedList * linkedList);

void linkedListExeptionHandler (LinkedList * linkedList);


#endif // LINKEDLIST_H_INCLUDED
