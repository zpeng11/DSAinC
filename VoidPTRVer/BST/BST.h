#ifndef BST_H
#define BST_H
#include "BinNode.h"
#include "BinTree.h"

typedef struct entry
{
    void * key;
    void * value;
}entry;
entry EntryCreate(const void *key, int KeyDataSize, const void *value, int ValueDataSize);
void EntryDestruct(entry *_entry);

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

BinNode ** BSTSearch(BST * _BST, const void * KeyTarget);
BinNode * BSTInseart(BST *_BST, const void * Key, const void * value);
BinNode *BSTRemoveAt(BinNode **x, BinNode **hot, int * RemovedColor);
int BSTRemove(BST * _BST, const void * key);
BinNode *BSTConnect34(BinNode *a, BinNode *b, BinNode *c, BinNode *T0, BinNode *T1, BinNode *T2, BinNode *T3, int(*upDateHeight)(BinNode*));
BinNode * BSTRotateAt(BinNode *v, int(*upDateHeight)(BinNode*));



#endif /*BST_H*/