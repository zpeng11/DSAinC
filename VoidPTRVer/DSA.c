#include "stack.h"
#include "vector.h"
#include "list.h"
#include "queue.h"
#include "BinNode.h"
#include "BinTree.h"

#include <stdio.h>

#define INT *(int *)
#define DOUBLE *(double *)

int IntIsEqual(const void *left, const void *right)
{
    return (int)*(int *)left == (int)*(int *)right;
}

int DoubleIsEqual(const void *left, const void *right)
{
    return (double)*(double *)left == (double)*(double *)right;
}

int IntIsGreater(const void *left, const void *right)
{
    return (int)*(int *)left > (int)*(int *)right;
}

int DoubleIsGreater(const void *left, const void *right)
{
    return (double)*(double *)left > (double)*(double *)right;
}

void print(void *a)
{
    int b = *(int *)  (*(BinNode **)a)->_data;
    printf("num is : %i\n", b);
}

int main()
{
    int i = 0;
    BinNode *root = BNodeCreate(&i, sizeof(int));
    i = 5;
    BNodeInsertAsRC(root, &i, sizeof(int));
    i = -2;
    BinNode *minus2 = BNodeInsertAsLC(root, &i, sizeof(int));
    i = -3;
    BNodeInsertAsLC(minus2, &i, 4);
    i = -1;
    BNodeInsertAsRC(minus2, &i, 4);
    vector V = BNodeLinVect(root);
    VecTraverse(&V, print);
}