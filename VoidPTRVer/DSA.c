#include "stack.h"
#include "vector.h"
#include "list.h"
#include "queue.h"
#include "BinNode.h"
#include "BinTree.h"
#include "BST.h"
#include "AVL.h"

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
#define Key(nodePTR) (*(int *)((*(entry *)((nodePTR)->_data)).key))
#define lc(BNodePTR) ((BNodePTR)->_lChild)
#define rc(BNodePTR) ((BNodePTR)->_rChild)
#define stature(p) ((p) ? (p)->_height : -1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define balfac(nodePTR) (stature(lc(nodePTR)) - stature(rc(nodePTR)))
#define Balanced(nodePTR) ((-2 < balfac(nodePTR)) && (balfac(nodePTR) < 2))
#define KeyPtr(nodePTR) ((*(entry *)((nodePTR)->_data)).key)
#define tallerChild(nodePTR) (((stature(lc(nodePTR))) >(stature(rc(nodePTR))) )? lc(nodePTR):rc(nodePTR))
#define FromParentTo(nodePTR) ((lc((nodePTR)->_parent) == (nodePTR))?  (&(lc((nodePTR)->_parent))) : (&(rc((nodePTR)->_parent))) )


int main()
{
    BST b = BSTCreate(sizeof(int), sizeof(double), IntIsEqual, IntIsGreater);
    int k = 0;
    double v = 34.73352;
    AVLInseart(&b, &k, &v);
    k = -1;
    AVLInseart(&b, &k, &v);
    k = 5;
    AVLInseart(&b, &k, &v);
    k = -3;
    AVLInseart(&b, &k, &v);
    k = 3;
    AVLInseart(&b, &k, &v);
    k = 7;
    AVLInseart(&b, &k, &v);
    k = -8;
    AVLInseart(&b, &k, &v);
    k = -9;
    AVLInseart(&b, &k, &v);
    k = -5;
    AVLInseart(&b, &k, &v);
    k = -4;
    AVLInseart(&b, &k, &v);
    k = 3;
    AVLRemove(&b, &k);
    k = 7;
    AVLRemove(&b, &k);
    printf("%i", Key(*FromParentTo(tallerChild(b._BinTree._root))));
    BSTDestruct(&b);



}