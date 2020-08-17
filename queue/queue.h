#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include "list.h"

typedef struct  queue
{
    list _list;
}queue;


queue QueueCreate(int DataSize);//create a queue which is link list in reality
#define QueueSize(queuePTR) (((list *)(queuePTR))->_size)//return element of queue
#define QueueEmpty(queuePTR) (!(((list *)(queuePTR))->_size))//check if the queue is empty
int QueueEnqueue(queue *_queue, const void * input);//insert an element at the end of queue
const void * QueueDequeue(queue *_queue);//take out element at the front of queue
void * QueueRear(queue *_queue);//check the end element in the queue
void * QueueFront(queue *_queue);//check the front element in the queue
void QueueDestruct(queue *_queue);//destruct and clean the queue




#endif