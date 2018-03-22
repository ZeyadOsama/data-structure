#ifndef QUEUESLL_H_INCLUDED
#define QUEUESLL_H_INCLUDED

#include <stdbool.h>

#include "linkedList.h"

//typedef struct QueueSLL { void * queue } QueueSLL;
typedef LinkedList QueueSLL;

/* defining enumeration for exceptions tags
 */
typedef enum
{
	NO_QUEUE_SLL_EXCEPETIONS ,
	FAILED_TO_CONSTRUCT_QUEUE_SLL ,
	QUEUE_SLL_IS_EMPTY ,
	QUEUE_SLL_IS_DESTRUCTED
} QueueSLLExceptionTags;


/* instantiating and destructing queue
 */
QueueSLL * constructQueueSLL ();
int destructQueueSLL (QueueSLL * queue);


/* main functions for queues
 */
int enqueue  (QueueSLL * queue , TYPE value);
TYPE dequeue  (QueueSLL * queue);


/* boolean checks functions
 */
bool isEmptyQueueSLL (QueueSLL * queue);


/* various utility functions
 */
void displayQueueSLL (QueueSLL * queue);
int unloadQueueSLL (QueueSLL * queue);

void queueExeptionHandler (QueueSLL * queue);


#endif // QUEUESLL_H_INCLUDED
