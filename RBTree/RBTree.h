#ifndef RBTREE_H
#define RBTREE_H

#include "BST.h"

#define RBT BST
#define RBTSearch BSTSearch
#define B 1
#define R 0
BinNode * RBTInsert(RBT * _RBT, const void * key, const void * value);
int RBTRemove(RBT *_RBT, const void *key);


void solveDoubleRed(RBT * _RBT, BinNode * x);
void solveDoubleBlack(RBT *_RBT, int xColor, BinNode *r);

#endif /*RBTREE_H*/