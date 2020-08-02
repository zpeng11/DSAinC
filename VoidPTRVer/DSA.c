#include "stack.h"
#include "vector.h"
#include "list.h"
#include "queue.h"
#include "BinNode.h"
#include "BinTree.h"

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
#define max(a,b) (((a)>(b))?(a):(b))
int main()
{
    printf("%i", max(1,2));
}