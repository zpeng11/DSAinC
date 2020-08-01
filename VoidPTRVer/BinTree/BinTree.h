#ifndef BINTREE_H
#define BINTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BinNode
{
    struct BinTree * _parent;
    struct BinTree * _lChild;
    struct BinTree * _rChild;
    void * _data;
    int _DataSize;
    int _height;
    int _npl;
    int color;
}BinNode;

int BNodeSize(BinNode *_BinNode);
int BNodeInsertAsLC(BinNode * old, BinNode * new);
int BNodeInsertAsRC(BinNode * old, BinNode * new);
BinNode * BNodeSucc(BinNode * _BinNode);
void BNodeTravLevel(BinNode * _BinNode, void(*callback)(void *));
void BNodeTravPre(BinNode * _BinNode, void(*callback)(void *));
void BNodeTravIn(BinNode * _BinNode, void(*callback)(void *));
void BNodeTravPost(BinNode * _BinNode, void(*callback)(void *));



#endif /*BINTREE_H*/