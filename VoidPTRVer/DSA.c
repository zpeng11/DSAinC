#include "stack.h"
#include "vector.h"
#include "list.h"
#include "queue.h"

#include <stdio.h>

#define INT *(int *)
#define DOUBLE *(double *)

int IntIsEqual(const void *left, const void * right)
{
    return (int)*(int *)left == (int)*(int *)right;
}

int DoubleIsEqual(const void *left, const void *right)
{
    return (double)*(double *) left == (double)*(double *) right;
}

int IntIsGreater(const void *left, const void *right)
{
    return (int)*(int *)left > (int)*(int *)right;
}

int DoubleIsGreater(const void *left, const void *right)
{
    return (double)*(double *)left > (double)*(double *)right;
}
int main()
{
    queue a = QueueCreate(sizeof(int));
    for (int i = 0; i<1000;i++)
    {
        srand(i);
        int b = rand()%1000;
        QueueEnqueue(&a, &b);
    }
    for(int i = 0; i<1000;i++)
    {
        printf("num is: %i\n", INT QueueDequeue(&a));
    }
    int i = QueueEmptey(&a);
    QueueDestruct(&a);



}