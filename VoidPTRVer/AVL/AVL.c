#include "AVL.h"
#define lc(BNodePTR) ((BNodePTR)->_lChild)
#define rc(BNodePTR) ((BNodePTR)->_rChild)
#define stature(p) ((p) ? (p)->_height : -1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define balfac(nodePTR) (stature(lc(nodePTR)) - stature(rc(nodePTR)))
#define Balanced(nodePTR) ((-2 < balfac(nodePTR)) && (balfac(nodePTR) < 2))
#define KeyPtr(nodePTR) ((*(entry *)((nodePTR)->_data)).key)
#define tallerChild(nodePTR) (((stature(lc(nodePTR))) > (stature(rc(nodePTR)))) ? lc(nodePTR) : rc(nodePTR))
#define FromParentTo(nodePTR) ((!((nodePTR)->_parent))?(&(_BST->_BinTree._root)):((lc((nodePTR)->_parent) == (nodePTR)) ? (&(lc((nodePTR)->_parent))) : (&(rc((nodePTR)->_parent)))))
#define IsLChild(nodePTR) ((nodePTR)->_parent->_lChild == (nodePTR))
#define IsRChild(nodePTR) ((nodePTR)->_parent->_rChild == (nodePTR))

BinNode *AVLInseart(AVL *_BST, const void *key, const void *value)
{
    BinNode *x = BSTSearch(_BST, key);
    if (x)
        return x;
    entry NewEntry = EntryCreate(key, _BST->_KeyDataSize, value, _BST->_ValueDataSize);
    if (_BST->_BinTree._size == 0)
    {
        x = _BST->_BinTree._root = BNodeCreate(&NewEntry, sizeof(entry));
    }
    else
    {
        if (_BST->KeyIsGreater(KeyPtr(_BST->_hot), key))
        {
            _BST->_hot->_lChild = x = BNodeCreate(&NewEntry, sizeof(entry));
        }
        else
        {
            _BST->_hot->_rChild = x = BNodeCreate(&NewEntry, sizeof(entry));
        }
    }
    _BST->_BinTree._size += 1;
    x->_parent = _BST->_hot;
    BinNode *g;
    for (g = x->_parent; g; g = g->_parent)
    {
        if (!Balanced(g))
        {
            *FromParentTo(g) = BSTRotateAt(tallerChild(tallerChild(g)));
            break;
        }
        else
        {
            BTreeUpdatHeight(g);
        }
    }
    return x;
}

int AVLRemove(AVL *_BST, const void *key)
{
    BinNode *x = AVLSearch(_BST, key);
    if (!x)
        return 0;
    BSTRemove(_BST, key);
    BinNode *g;
    for (g = _BST->_hot; g; g = g->_parent)
    {
        if (!Balanced(g))
        {
            g = *FromParentTo(g) = BSTRotateAt(tallerChild(tallerChild(g)));
            BTreeUpdatHeight(g);
        }
    }
    return 1;
}
