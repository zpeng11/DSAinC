#ifndef BST_H
#define BST_H
#include "BinNode.h"
#include "BinTree.h"

typedef struct entry
{
    void * key;
    void * value;
}entry;

typedef struct BST
{
    BinTree _BinTree;
    int _KeyDataSize;
    int _ValueDataSize;
    BinNode * _hot;
    int (* KetIsEqual)(const void *, const void *);
    int (* KeyIsGreater)(const void * ,const void *);
}BST;

BST BSTCreate(int KeyDataSize, int ValueDataSize, int (* KetIsEqual)(const void *, const void *),int (* KeyIsGreater)(const void * ,const void *) );
void BSTDestruct(BST * _BST);

BinNode * BSTSearch(BST * _BST, const void * KeyTarget);
BinNode * BSTInseart(BST *_BST, const void * Key, const void * value);
int BSTRemove(BST * _BST, const void * key);
BinNode * BSTConnect34(BinNode * , BinNode *, BinNode *, BinNode *, BinNode *, BinNode *, BinNode *);
BinNode * BSTRotateAt(BinNode *);



#endif /*BST_H*/