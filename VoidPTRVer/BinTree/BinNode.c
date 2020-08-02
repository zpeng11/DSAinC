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
    BinNode *temp = _BinNode;
    if (_BinNode)
        StackPush(&S, &temp);
    while (!StackEmpty(&S))
    {
        _BinNode = BNodePTR StackPop(&S);
        callback(_BinNode->_data);
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
    }
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
    BinNode *temp;
    while (!StackEmpty(&S))
    {
        temp = _BinNode;
        StackPush(&S, &temp);
        if(_BinNode->_rChild)
        {
            temp = _BinNode->_rChild;
            StackPush(&S, &temp);
        }
        if(_BinNode->_lChild)
        {
            _BinNode = _BinNode->_lChild;
        }
        else
        {
            temp = BNodePTR StackPop(&S);
            if(temp == _BinNode)
            {
                callback(_BinNode->_data);
                _BinNode = BNodePTR StackPop(&S);
            }
            else
            {
                _BinNode = temp;
            }
        }
        
    }
    StackDestruct(&S);
}