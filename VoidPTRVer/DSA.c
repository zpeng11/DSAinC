#include "stack.h"
#include "vector.h"
#include "list.h"
#include "queue.h"
#include "BinNode.h"
#include "BinTree.h"
#include "BST.h"

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
#define Key(nodePTR) *(int *)((*(entry *)((nodePTR)->_data)).key) 
int main()
{
    BST b = BSTCreate(sizeof(int), sizeof(double), IntIsEqual, IntIsGreater);
    int k = 0;
    double v = 34.73352;
    BSTInseart(&b, &k, &v);
    k = -1;
    BSTInseart(&b, &k, &v);
    k = 5;
    BSTInseart(&b, &k, &v);
    k = -3;
    BSTInseart(&b, &k, &v);
    k = 3;
    BSTInseart(&b, &k, &v);
    k = 7;
    BSTInseart(&b, &k, &v);
    k = -8;
    BSTInseart(&b, &k, &v);
    k = -9;
    BSTInseart(&b, &k, &v);
    k = -5;
    BSTInseart(&b, &k, &v);
    k = -4;
    BSTInseart(&b, &k, &v);
    k = -1;
    BSTRemove(&b, &k);



}