#include "BST.h"
#define KeyPtr(nodePTR) ((*(entry *)((nodePTR)->_data)).key)
#define ENTRY *(entry *)
#define Key(nodePTR) *(int *)((*(entry *)((nodePTR)->_data)).key)
#define IsLChild(nodePTR) ((nodePTR)->_parent->_lChild == (nodePTR))
#define IsRChild(nodePTR) ((nodePTR)->_parent->_rChild == (nodePTR))
#define lc(BNodePTR) ((BNodePTR)->_lChild)
#define rc(BNodePTR) ((BNodePTR)->_rChild)
#define stature(p) ((p) ? (p)->_height : -1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define balfac(nodePTR) (stature(lc(nodePTR)) - stature(rc(nodePTR)))
#define Balanced(nodePTR) ((-2 < balfac(nodePTR)) && (balfac(nodePTR) < 2))
#define KeyPtr(nodePTR) ((*(entry *)((nodePTR)->_data)).key)
#define tallerChild(nodePTR) (((stature(lc(nodePTR))) >(stature(rc(nodePTR))) )? lc(nodePTR):rc(nodePTR))
#define FromParentTo(nodePTR) ((lc((nodePTR)->_parent) == (nodePTR))?  (&(lc((nodePTR)->_parent))) : (&(rc((nodePTR)->_parent))) )


BST BSTCreate(int KeyDataSize, int ValueDataSize, int (*KetIsEqual)(const void *, const void *), int (*KeyIsGreater)(const void *, const void *))
{
    BST new = {.KetIsEqual = KetIsEqual,
               .KeyIsGreater = KeyIsGreater,
               ._hot = NULL,
               ._KeyDataSize = KeyDataSize,
               ._ValueDataSize = ValueDataSize,
               ._BinTree._DataSize = sizeof(entry),
               ._BinTree._root = NULL,
               ._BinTree._size = 0};
    return new;
}

void BSTDestruct(BST *_BST)
{
    vector v = BNodeLinVect(_BST->_BinTree._root);
    BinNode *temp;
    while (VecSize(&v))
    {
        temp = *(BinNode **)VecPopBack(&v);
        EntryDestruct(temp->_data);
        BNodeDestruct(temp);
    }
}

BinNode **SearchIn(BST *_BST, BinNode **v, const void *KeyTarget)
{
    if (!(*v) || _BST->KetIsEqual(KeyTarget, KeyPtr(*v)))
        return v;
    _BST->_hot = *v;
    return SearchIn(_BST, (_BST->KeyIsGreater(KeyPtr(*v), KeyTarget) ? &((*v)->_lChild) : &((*v)->_rChild)), KeyTarget);
}

BinNode **BSTSearch(BST *_BST, const void *KeyTarget)
{
    _BST->_hot = NULL;
    return SearchIn(_BST, &(_BST->_BinTree._root), KeyTarget);
}

entry EntryCreate(const void *key, int KeyDataSize, const void *value, int ValueDataSize)
{
    entry new;
    new.key = malloc(KeyDataSize);
    new.value = malloc(ValueDataSize);
    memcpy(new.key, key, KeyDataSize);
    memcpy(new.value, value, ValueDataSize);
    return new;
}

void EntryDestruct(entry *_entry)
{
    free(_entry->key);
    free(_entry->value);
}

BinNode *BSTInseart(BST *_BST, const void *key, const void *value)
{
    BinNode *temp = *BSTSearch(_BST, key);
    if (temp)
        return temp;
    _BST->_BinTree._size += 1;
    entry NewEntry = EntryCreate(key, _BST->_KeyDataSize, value, _BST->_ValueDataSize);
    if (_BST->_BinTree._size == 1)
    {
        temp = _BST->_BinTree._root = BNodeCreate(&NewEntry, sizeof(entry));
    }
    else
    {
        if (_BST->KeyIsGreater(key, KeyPtr(_BST->_hot)))
            temp = BNodeInsertAsRC(_BST->_hot, &NewEntry, sizeof(entry));
        else
            temp = BNodeInsertAsLC(_BST->_hot, &NewEntry, sizeof(entry));
    }
    BTreeUpdateHeightAbove(temp);
    return temp;
}

BinNode *BSTRemoveAt(BinNode **x, BinNode **hot, int * RemovedColor)
{
    BinNode *w = *x;
    BinNode *succ = NULL;
    if (!(*x)->_lChild)//case that only one or zero child
    {
        succ = (*x) = (*x)->_rChild;
    }
    else if (!(*x)->_rChild)//same only one or zero child
    {
        succ = *x = (*x)->_lChild;
    }
    else//two children, we find the succ of the node in InOrder iteration and exchange entry, succ only has one child
    {
        w = BNodeSucc(w);
        entry temp = ENTRY w->_data;
        ENTRY w->_data = ENTRY (*x)->_data;
        ENTRY (*x)->_data = temp;
        BinNode *u = w->_parent;
        if (u == *x)
            u->_rChild = succ = w->_rChild;
        else
            u->_lChild = succ = w->_rChild;
    }
    *hot = w->_parent;
    if (succ)
        succ->_parent = *hot;
    *FromParentTo(w) = succ;
    if(RemovedColor != NULL)
        *RemovedColor = w->_color;//for RBTree to record removed color
    EntryDestruct(w->_data);
    BNodeDestruct(w);
    return succ;
}

int BSTRemove(BST *_BST, const void *key)
{
    BinNode **node_2_remove = BSTSearch(_BST, key);
    if (!(*node_2_remove))
        return 0;
    BSTRemoveAt(node_2_remove, &(_BST->_hot), NULL);
    _BST->_BinTree._size -= 1;
    BTreeUpdateHeightAbove(_BST->_hot);
    return 1;
}

BinNode *BSTConnect34(BinNode *a, BinNode *b, BinNode *c, BinNode *T0, BinNode *T1, BinNode *T2, BinNode *T3, int(*upDateHeight)(BinNode*))
{
    a->_lChild = T0;
    if (T0)
        T0->_parent = a;
    a->_rChild = T1;
    if (T1)
        T1->_parent = a;
    upDateHeight(a);
    c->_lChild = T2;
    if (T2)
        T2->_parent = c;
    c->_rChild = T3;
    if (T3)
        T3->_parent = c;
    upDateHeight(c);
    b->_lChild = a;
    a->_parent = b;
    b->_rChild = c;
    c->_parent = b;
    upDateHeight(b);
    return b;
}


BinNode * BSTRotateAt(BinNode *v, int(*upDateHeight)(BinNode*))
{
    BinNode * p =  v->_parent;
    BinNode * g =  p->_parent;
    if(IsLChild(p))
    {
        if(IsLChild(v))
        {
            p->_parent = g->_parent;
            return BSTConnect34(v,p,g,lc(v), rc(v), rc(p),rc(g),upDateHeight);
        }
        else
        {
            v->_parent = g->_parent;
            return BSTConnect34(p, v, g, lc(p), lc(v), rc(v), rc(g), upDateHeight);
        }
    }
    else
    {
        if(IsLChild(v))
        {
            v->_parent = g->_parent;
            return BSTConnect34(g,v,p, lc(g), lc(v), rc(v), rc(p), upDateHeight);
        }
        else
        {
            p->_parent = g->_parent;
            return BSTConnect34(g, p, v, lc(g), lc(p), lc(v), rc(v), upDateHeight);
        }
        
    }
    
}