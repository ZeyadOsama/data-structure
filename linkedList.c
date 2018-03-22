/*
 *
 * C Program To Implement Linked List Using Dynamic Memory Allocation.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"


/* creates a new node.
 */
Node * newNode (TYPE value)
{
	// dynamically allocating memory for linked list
	Node * node = malloc(sizeof(Node));

	// failure check
	if(node == NULL)
		return NULL;

	// if successfully allocated
	// initializing node content
	node->value = value;
	node->next = NULL;

	return node;
}


/* initialize linked list.
 */
LinkedList * constructLinkedList ()
{
	// dynamically allocating memory for linked list
	LinkedList * linkedList = malloc(sizeof(LinkedList));

	// failure check
	if(linkedList == NULL)
		return NULL;

	// if successfully allocated
	// initializing linked list content
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->exception = LINKEDLIST_IS_EMPTY;

	return linkedList;
}


int destructLinkedList (LinkedList * linkedList)
{
	while ( !isEmptyLinkedList(linkedList) )
		removeFromHead(linkedList);

	linkedList->exception = LINKEDLIST_IS_DESTRUCTED;
	linkedList = NULL;

	// deallocate
	free(linkedList);

	return NO_LINKEDLIST_EXCEPETIONS;
}


int insertToHead (LinkedList * linkedList , TYPE value)
{
	Node * node = newNode(value);

	node->next = linkedList->head;

	linkedList->head = node;

	// tail has not been initialized yet
	if(linkedList->tail == NULL)
		linkedList->tail = node;

	linkedList->length++;

	// no thrown exceptions
	return linkedList->exception = NO_LINKEDLIST_EXCEPETIONS;
}


int insertToTail (LinkedList * linkedList , TYPE value)
{
	Node * node = newNode(value);

	// temporary node
	Node * tail = linkedList->tail;

	linkedList->tail = node;

	// tail is NULL so is head
	if (tail == NULL)
		linkedList->head = node;

	else
		tail->next = node;

	linkedList->length++;

	// no thrown exceptions
	return linkedList->exception = NO_LINKEDLIST_EXCEPETIONS;
}


int insertToIndex (LinkedList * linkedList , TYPE value , int index)
{
	// sanity check
	if (index > linkedList->length)
		return RANGE_OUT_OF_BOUNDS;

	if (index == linkedList->length)
		return insertToTail(linkedList,value);

	if (index == 1)
		return insertToHead(linkedList,value);

	Node * currentNode = linkedList->head;

	// navigate through list
	int i;
	for (i=2 ; i<index ; i++)
		// go to next node in linked list
        currentNode = currentNode->next;

	Node * node = newNode(value);

	node->next = currentNode->next;
	currentNode->next = node;

	linkedList->length++;

	// no thrown exceptions
	return linkedList->exception = NO_LINKEDLIST_EXCEPETIONS;
}


int removeFromHead (LinkedList * linkedList)
{
	if ( !isEmptyLinkedList(linkedList) )
	{
		Node * headTemp = linkedList->head;

		// reserve data before deallocating
		// to be returned
		TYPE value = headTemp->value;
		linkedList->head = headTemp->next;

		// deallocate
		free(headTemp);

		if ( isEmptyLinkedList(linkedList) )
			linkedList->tail = NULL;

		linkedList->length--;

		return value;
	}

	return LINKEDLIST_IS_EMPTY;
}


/*
 */
int removeFromTail (LinkedList * linkedList)
{
	return removeFromIndex (linkedList , linkedList->length);
}


/*
 */
int removeFromIndex (LinkedList * linkedList , int index)
{
	// sanity check
	if (index > linkedList->length)
		return RANGE_OUT_OF_BOUNDS;

	if (index == 1)
		return removeFromHead(linkedList);


	Node * currentNode = linkedList->head;
	Node * prevNode = NULL;

	// navigate through list
	int i;
	for (i=1 ; i<index ; i++)
    {
        prevNode = currentNode;

		// go to next node in linked list
		currentNode = currentNode->next;
    }

    prevNode->next = currentNode->next;

	free(currentNode);

	linkedList->length--;

	return 0;
}


/*
 */
TYPE getValueOf (LinkedList * linkedList , int index)
{
	// sanity check
	if (index > linkedList->length)
		return RANGE_OUT_OF_BOUNDS;

	Node * currentNode = linkedList->head;

	// navigate through list
	int i;
	for (i=1 ; i<index ; i++)
		// go to next node in linked list
		currentNode = currentNode->next;


	return currentNode->value;
}


/* boolean check.
 */
bool isEmptyLinkedList (LinkedList * linkedList)
{
	return linkedList->head == NULL ? true : false;
}


/* searches for a given target within a given linked list.
 */
Node * searchLinkedList (LinkedList * linkedList , TYPE target)
{
	if(linkedList->head == NULL)
		return NULL;

	Node * currentNode = linkedList->head;

	// navigate through list
	while (currentNode->value != target)
	{
		// tail reached
		if(currentNode->next == NULL)
			return NULL;

		// go to next node in linked list
		currentNode = currentNode->next;
	}

	// target found
	// return current node
	return currentNode;
}


void displayLinkedList (LinkedList * linkedList)
{
	Node * currentNode = linkedList->head;

	printf("[ ");

	// navigate through list
	while (currentNode != NULL)
	{
		printf("%i ", currentNode->value);

		// go to next node in linked list
		currentNode = currentNode->next;
	}

	printf("]\n");

	return;
}


/* copies a linked list into one another.
 */
void copyLinkedList (LinkedList * linkedListDestination , LinkedList * linkedListSource)
{
	unloadLinkedList(linkedListDestination);

	int POSITION = 1;

	insertToHead(linkedListDestination, getValueOf(linkedListSource, POSITION++));

	while (POSITION <= linkedListSource->length)
		insertToTail(linkedListDestination, getValueOf(linkedListSource, POSITION++));


	return;
}


/*
 */
LinkedList * reverseLinkedList(LinkedList * linkedList)
{
    Node * current = linkedList->head;

    Node * prev = NULL;
    Node * next = NULL;

    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;

        current = next;
    }

    linkedList->head = prev;

    return linkedList;
}


/* ascendingly sort a given linked list
 */
LinkedList * sortLinkedList (LinkedList * linkedList)
{
    Node *current, *next;

    // iterators
    int i, j;
    int length = linkedList->length;

    // bubble sort
    for (i = 0 ; i < (linkedList->length - 1) ; i++ , length--)
    {
        // two contiguous temporary nodes
        current = linkedList->head ;
        next = linkedList->head->next ;

        for (j = 1 ; j < length ; j++)
        {
            if ( current->value > next->value )
            {
                TYPE tempValue = current->value ;
                current->value = next->value;
                next->value = tempValue ;
            }

            current = current->next;
            next = next->next;
        }
    }

    return linkedList;
}


/* expects one parameter: any given linkedList address.
 * functionality: remove all content of a given linkedList
 */
int unloadLinkedList (LinkedList * linkedList)
{
	while (!isEmptyLinkedList(linkedList))
		removeFromHead(linkedList);

	linkedList->head = NULL;
	linkedList->tail = NULL;

	// throw exception to assure no removing
	return linkedList->exception = LINKEDLIST_IS_EMPTY;
}


/* handles exceptions that may occur in a given linked list.
 */
void linkedListExeptionHandler (LinkedList * linkedList)
{
	switch(linkedList->exception)
	{
		// no thrown exceptions
		case NO_LINKEDLIST_EXCEPETIONS:
			return;

		case LINKEDLIST_IS_EMPTY:
			fprintf(stderr,"linked list is empty\n");
			return;

		case LINKEDLIST_IS_DESTRUCTED:
			fprintf(stderr,"linked list is destructed\n");
			return;
	}

	return;
}
