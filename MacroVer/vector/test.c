#include <stdio.h>
#include "vectorPTR.h"
#include "vector.h"
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
    vector a = VecCreate(sizeof(int));
    for (int i = 0; i<1000;i++)
    {
        srand(i);
        int random =rand()%100;
        VecPushBack(&a, &random );
    }
    VecMergeSortOL(&a, IntIsGreater);
    printf("%i", INT VecGet(&a, VecSize(&a)-1));

    

    
}