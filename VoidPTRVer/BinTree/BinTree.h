#ifndef BINTREE_H
#define BINTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinNode.h"





typedef struct BinTree
{
    BinNode * _root;
    int _DataSize;
    int _size;
}BinTree;

int BTreeUpdatHeight(BinNode * _BinNode);
void BTreeUpdateHeightAbove(BinNode *_BinNode);
#define BTreeSize(BTreePTR) ((BTreePTR)-> _size)
#define BTreeEmpty(BTreePTR) (!((BTreePTR)->_size))
#define BTreeRoot(BTreePTR) ((BTreePTR)->_root)
BinNode * BTreeInsertAsRC(BinTree *_BinTree, BinNode * node_2_insert, const void *);
BinNode * BTreeInsertAsLC(BinTree *_BinTree, BinNode * node_2_insert, const void *);

#endif /*BINTREE_H*/