#include "BinNode.h"
#define lc(BNodePTR) ((BNodePTR)->_lChild)
#define rc(BNodePTR) ((BNodePTR)->_rChild)
#define stature(p) ((p) ? (p)->_height : -1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define BNodePTR *(BinNode **)

BinNode *BNodeCreate(const void *input, int DataSize)
{
    BinNode *ptr = (BinNode *)malloc(sizeof(BinNode));
    ptr->_data = malloc(DataSize);
    memcpy(ptr->_data, input, DataSize);
    ptr->_parent = NULL;
    ptr->_rChild = NULL;
    ptr->_lChild = NULL;
    ptr->_color = 0;
    ptr->_npl = 0;
    ptr->_height = 0;
    return ptr;
}

BinNode *BNodeInsertAsLC(BinNode *old, const void *input, int DataSize)
{
    BinNode *new = BNodeCreate(input, DataSize);
    new->_parent = old;
    old->_lChild = new;
    return new;
}

BinNode *BNodeInsertAsRC(BinNode *old, const void *input, int DataSize)
{
    BinNode *new = BNodeCreate(input, DataSize);
    new->_parent = old;
    old->_rChild = new;
    return new;
}

int BNodeSize(const BinNode *_BinNode)
{
    int s = 1;
    if (_BinNode->_lChild)
        s += BNodeSize(_BinNode->_lChild);
    if (_BinNode->_rChild)
        s += BNodeSize(_BinNode->_rChild);
    return s;
}

void BNodeTravPreR(BinNode *_BinNode, void (*callback)(void *))
{
    if (!_BinNode)
        return;
    callback(_BinNode->_data);
    BNodeTravPreR(_BinNode->_lChild, callback);
    BNodeTravPreR(_BinNode->_rChild, callback);
}

void BNodeTravPreI(BinNode *_BinNode, void (*callback)(void *))
{
    stack S = StackCreate(sizeof(BinNode *));
    BinNode *temp = NULL;
    StackPush(&S, &temp);
    do
    {
        callback(_BinNode->_data);
        if (_BinNode->_rChild)
        {
            temp = _BinNode->_rChild;
            StackPush(&S, &temp);
        }
        if (_BinNode->_lChild)
        {
            _BinNode = _BinNode->_lChild;
        }
        else
        {
            _BinNode = BNodePTR StackPop(&S);
        }

    } while (_BinNode);
    StackDestruct(&S);
}

void visitAlongLeftBranch(BinNode *node, void (*callback)(void *), stack *S)
{
    BinNode *temp;
    while (node)
    {
        callback(node->_data);
        temp = node->_rChild;
        StackPush(S, &temp);
        node = node->_lChild;
    }
}

void BNodeTravPreI2(BinNode *_BinNode, void (*callback)(void *))
{
    stack S = StackCreate(sizeof(BinNode *));
    while (1)
    {
        visitAlongLeftBranch(_BinNode, callback, &S);
        if (StackEmpty(&S))
            break;
        _BinNode = BNodePTR StackPop(&S);
    }
    StackDestruct(&S);
}

void BNodeTravInR(BinNode *_BinNode, void (*callback)(void *))
{
    if (!_BinNode)
        return;
    BNodeTravInR(_BinNode->_lChild, callback);
    callback(_BinNode->_data);
    BNodeTravInR(_BinNode->_rChild, callback);
}

void goAlongLeftBranch(BinNode *node, stack *S)
{
    BinNode *temp;
    while (node)
    {
        temp = node;
        StackPush(S, &temp);
        node = node->_lChild;
    }
}

void BNodeTravInI(BinNode *_BinNode, void (*callback)(void *))
{
    stack S = StackCreate(sizeof(BinNode *));
    while (1)
    {
        goAlongLeftBranch(_BinNode, &S);
        if (StackEmpty(&S))
            break;
        _BinNode = BNodePTR StackPop(&S);
        callback(_BinNode->_data);
        _BinNode = _BinNode->_rChild;
    }
    StackDestruct(&S);
}

BinNode *BNodeSucc(BinNode *_BinNode) 
{
    if(!_BinNode->_rChild)return NULL;
    BinNode * temp = _BinNode->_rChild;
    while(temp->_lChild)
    {
        temp = temp->_lChild;
    }
    return temp;
}


void BNodeTravLevelI(BinNode *_BinNode, void (*callback)(void *))
{
    queue Q = QueueCreate(sizeof(BinNode *));
    BinNode *temp = _BinNode;
    QueueEnqueue(&Q, &temp);
    while (!QueueEmpty(&Q))
    {
        _BinNode = BNodePTR QueueDequeue(&Q);
        callback(_BinNode->_data);
        if (_BinNode->_lChild)
        {
            temp = _BinNode->_lChild;
            QueueEnqueue(&Q, &temp);
        }
        if (_BinNode->_rChild)
        {
            temp = _BinNode->_rChild;
            QueueEnqueue(&Q, &temp);
        }
    }
}

void BNodeTravPostR(BinNode *_BinNode, void (*callback)(void *))
{
    if (!_BinNode)
        return;
    BNodeTravPostR(_BinNode->_lChild, callback);
    BNodeTravPostR(_BinNode->_rChild, callback);
    callback(_BinNode->_data);
}

void BNodeTravPostI(BinNode *_BinNode, void (*callback)(void *))
{
    stack S = StackCreate(sizeof(BinNode *));
    stack S2 = StackCreate(sizeof(void *));
    BinNode *temp = _BinNode;
    StackPush(&S, &temp);
    while (!StackEmpty(&S))
    {
        _BinNode = BNodePTR StackPop(&S);
        if (_BinNode->_lChild)
        {
            temp = _BinNode->_lChild;
            StackPush(&S, &temp);
        }
        if (_BinNode->_rChild)
        {
            temp = _BinNode->_rChild;
            StackPush(&S, &temp);
        }
        temp = _BinNode->_data;
        StackPush(&S2, &temp);
    }
    while (!StackEmpty(&S2))
    {
        void *ptr = *(void **)StackPop(&S2);
        callback(ptr);
    }
    StackDestruct(&S);
    StackDestruct(&S2);
}



vector BNodeLinVect(BinNode * _BinNode)
{
    vector V = VecCreate(sizeof(BinNode *), NULL, NULL);
    stack S = StackCreate(sizeof(BinNode *));
    BinNode * temp;
    while (1)
    {
        goAlongLeftBranch(_BinNode, &S);
        if (StackEmpty(&S))
            break;
        temp = _BinNode = BNodePTR StackPop(&S);
        VecPushBack(&V, &temp);
        _BinNode = _BinNode->_rChild;
    }
    StackDestruct(&S);
    return V;
}


void BNodeDestruct(BinNode *_BinNode)
{
    free(_BinNode->_data);
    free(_BinNode);
}

void BNodeDestructAll(BinNode *_BinNode)
{
    vector V = BNodeLinVect(_BinNode);
    while(VecSize(&V))
    {
        BNodeDestruct(BNodePTR VecPopBack(&V));
    }
    VecDestruct(&V);
}