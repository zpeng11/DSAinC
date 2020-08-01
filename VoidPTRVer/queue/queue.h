#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct  queue
{
    list _list;
}queue;


queue QueueCreate(void);
int QueueEmptey(queue * _queue);
int QueueSize(queue * _queue);



#endif