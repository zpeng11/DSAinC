#ifndef BINNODE_H
#define BINNODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#include "vector.h"

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
void BNodeTravLevelI(BinNode *_BinNode, void (*callback)(void *));//traverse by level
void BNodeTravPreR(BinNode *_BinNode, void (*callback)(void *));//traverse by pre order with recurssion
void BNodeTravPreI(BinNode *_BinNode, void (*callback)(void *));//traverse by pre order with iteration
void BNodeTravPreI2(BinNode *_BinNode, void (*callback)(void *));//second method of preoder iteration
void BNodeTravInR(BinNode *_BinNode, void (*callback)(void *));//traverse by in order with recurssion
void BNodeTravInI(BinNode *_BinNode, void (*callback)(void *));// traverse by in oreder with iteration
void BNodeTravPostR(BinNode *_BinNode, void (*callback)(void *));//traverse by post order with recurssion
void BNodeTravPostI(BinNode *_BinNode, void (*callback)(void *));//traverse by post order with iteration
vector BNodeLinVect(BinNode * _BinNode);//return an created element that contains pointer to each node in inorder

void BNodeDestruct(BinNode *_BinNode);//destruct an node 
void BNodeDestructAll(BinNode *_BinNode);//destruct all offsprings of a node

#endif /*BINNODE_h*/