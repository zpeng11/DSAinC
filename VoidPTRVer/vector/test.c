#include <stdio.h>
#include "vectorPTR.h"
#define INT *(int *)


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
    vector  a = VecCreate(sizeof(vector));
    vector b = VecCreate(sizeof(int));
    VecPushBack(&a, &b);
    int c = 6;
    VecPushBack(VecGet(&a,0), &c);
    VecTraverse(&a, VecDestruct);
    VecDestruct(&a);
    

    
}