#include <stdio.h>
#include "list.h"


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
    list a = ListCreate(sizeof(int));


}