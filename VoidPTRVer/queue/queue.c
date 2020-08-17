#include "queue.h"

queue QueueCreate(int DataSize)
{
    queue new;
    new._list = ListCreate(DataSize, NULL, NULL);
    return new;

}




int QueueEnqueue(queue *_queue, const void * input)
{
    ListInsertAsLast((list *)_queue, input);
}


const void * QueueDequeue(queue *_queue)
{
    return ListRemove((list *)_queue, 0);
}

void * QueueRear(queue *_queue)
{
    return ListGet((list *)_queue, QueueSize(_queue)-1);
}

void * QueueFront(queue *_queue)
{
    return ListGet((list *)_queue, 0);
}


void QueueDestruct(queue *_queue)
{
    ListDestruct((list *)_queue);
}