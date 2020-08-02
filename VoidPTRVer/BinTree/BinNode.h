#ifndef BINNODE_H
#define BINNODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

typedef struct BinNode
{
    struct BinNode *_parent;
    struct BinNode *_lChild;
    struct BinNode *_rChild;
    void *_data;
    int _height;
    int _npl;
    int _color;
} BinNode;

BinNode *BNodeCreate(const void *input, int DataSize);

int BNodeSize(const BinNode *_BinNode);

BinNode *BNodeInsertAsLC(BinNode *node_2_insert, const void *input, int DataSize); //The lc of the old should be null
BinNode *BNodeInsertAsRC(BinNode *node_2_insert, const void *input, int DataSize); //The rc of the old should be null

BinNode *BNodeSucc(BinNode *_BinNode); //inorder succ
void BNodeTravLevelI(BinNode *_BinNode, void (*callback)(void *));
void BNodeTravPreR(BinNode *_BinNode, void (*callback)(void *));
void BNodeTravPreI(BinNode *_BinNode, void (*callback)(void *));
void BNodeTravPreI2(BinNode *_BinNode, void (*callback)(void *));
void BNodeTravInR(BinNode *_BinNode, void (*callback)(void *));
void BNodeTravInI(BinNode *_BinNode, void (*callback)(void *));
void BNodeTravPostR(BinNode *_BinNode, void (*callback)(void *));
void BNodeTravPostI(BinNode *_BinNode, void (*callback)(void *));

void BNodeDestruct(BinNode *_BinNode);

#endif /*BINNODE_h*/