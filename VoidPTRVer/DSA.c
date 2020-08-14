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
    printf("\033[2J");
    printf("\033[=0h");
    printf("\x1B[31mTexting\033[0m\t\t");
    printf("\x1B[32mTexting\033[0m\t\t");
    printf("\x1B[33mTexting\033[0m\t\t");
    printf("\x1B[34mTexting\033[0m\t\t");
    printf("\x1B[35mTexting\033[0m\n");

    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[37mTexting\033[0m\t\t");
    printf("\x1B[93mTexting\033[0m\n");

    printf("\033[3;42;30mTexting\033[0m\t\t");
    printf("\033[3;43;30mTexting\033[0m\t\t");
    printf("\033[3;44;30mTexting\033[0m\t\t");
    printf("\033[3;104;30mTexting\033[0m\t\t");
    printf("\033[3;100;30mTexting\033[0m\n");

    printf("\033[3;47;35mTexting\033[0m\t\t");
    printf("\033[2;47;35mTexting\033[0m\t\t");
    printf("\033[1;47;35mTexting\033[0m\t\t");
    printf("\t\t");
    printf("\n");
    printf("helloworld");
    system("pause");
    system("dir");
    }