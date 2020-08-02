#include "BinTree.h"
#define lc(BNodePTR) ((BNodePTR)->_lChild)
#define rc(BNodePTR) ((BNodePTR)->_rChild)
#define stature(p) ((p) ? (p)->_height : -1)
#define max(a, b) (((a) > (b)) ? (a) : (b))

int BTreeUpdatHeight(BinNode *_BinNode)
{
    _BinNode->_height = 1 + max(stature(_BinNode->_lChild), stature(_BinNode->_rChild));
    return _BinNode->_height;
}

void BTreeUpdateHeightAbove(BinNode *_BinNode)
{
    while (_BinNode)
    {
        BTreeUpdatHeight(_BinNode);
        _BinNode = _BinNode->_parent;
    }
}

BinNode *BTreeInsertAsRC(BinTree *_BinTree, BinNode *node_2_insert, const void *input)
{
    _BinTree->_size += 1;
    BNodeInsertAsRC(node_2_insert, input, _BinTree->_DataSize);
    BTreeUpdateHeightAbove(node_2_insert);
    return node_2_insert->_rChild;
}

BinNode *BTreeInsertAsLC(BinTree *_BinTree, BinNode *node_2_insert, const void *input)
{
    _BinTree->_size += 1;
    BNodeInsertAsLC(node_2_insert, input, _BinTree->_DataSize);
    BTreeUpdateHeightAbove(node_2_insert);
    return node_2_insert->_lChild;
}