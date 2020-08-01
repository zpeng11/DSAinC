#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include "list.h"

typedef struct  queue
{
    list _list;
}queue;


queue QueueCreate(int DataSize);
int QueueEmptey(queue * _queue);
int QueueSize(queue * _queue);
int QueueEnqueue(queue *_queue, const void * input);
const void * QueueDequeue(queue *_queue);
const void * QueueRear(queue *_queue);
const void * QueueFront(queue *_queue);
void QueueDestruct(queue *_queue);




#endif