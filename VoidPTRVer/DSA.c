#include "stack.h"
#include "vector.h"
#include "list.h"
#include "queue.h"
#include "BinNode.h"
#include "BinTree.h"
#include "BST.h"
#include "AVL.h"
#include <conio.h>
#include <windows.h>
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
    printf("%i", -1<<1);
}