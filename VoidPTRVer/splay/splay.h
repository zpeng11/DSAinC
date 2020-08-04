#ifndef SPLAY_H
#define SPLAY_H

#include "BST.h"
#define splay BST
#define SplayCreate BSTCreate
#define SplayDestruct BSTDestruct

BinNode * Splay(BinNode *);
BinNode * SplaySearch(splay * _splay, const void * key);
BinNode * SplayInsert(splay * _splay, const void * key, const void * value);
int SplayRemove(splay * _splay, const void * key);


#endif /*SPLAY_H*/