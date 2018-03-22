/*
 *
 * C Program To Implement Dynamic Queue Using Linked List.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "queueSLL.h"


/* allocates memory for queue's linked list
 */
QueueSLL * constructQueueSLL ()
{
	return constructLinkedList ();
}


/* expects one parameter: any given queue address.
 */
int destructQueueSLL (QueueSLL * queue)
{
	destructLinkedList (queue);

	return NO_QUEUE_SLL_EXCEPETIONS;
}


/* expects two parameter: any given queue address / to be inserted data.
 * functionality: add data to rear (tail) of queue.
 */
int enqueue (QueueSLL * queue , TYPE value)
{
	insertToTail (queue, value);

	// no thrown exceptions
	return queue->exception = NO_QUEUE_SLL_EXCEPETIONS;
}


/* expects one parameter: any given queue address.
 * functionality: remove data from top (head) of queue.
 * could be assigned to variables.
 */
TYPE dequeue (QueueSLL * queue)
{
	return removeFromHead (queue);
}


/* boolean check.
 */
bool isEmptyQueueSLL (QueueSLL * queue)
{
	return isEmptyLinkedList(queue);
}


void displayQueueSLL (QueueSLL * queue)
{
	displayLinkedList(queue);
}


/* remove all nodes, but does not destruct inner linked list
 */
int unloadQueueSLL (QueueSLL * queue)
{
	return unloadLinkedList(queue);
}


/* handles exceptions that may occur in a given queue.
 */
void queueExeptionHandler (QueueSLL * queue)
{
	switch(queue->exception)
	{
		// no thrown exceptions
		case NO_QUEUE_SLL_EXCEPETIONS:
			return;

		case QUEUE_SLL_IS_EMPTY:
			fprintf(stderr,"queue is empty\n");
			return;

		case QUEUE_SLL_IS_DESTRUCTED:
			fprintf(stderr,"queue is destructed\n");
			return;
	}
}
