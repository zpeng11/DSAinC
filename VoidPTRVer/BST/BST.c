#include "BST.h"
#define KeyPtr(nodePTR) ((*(entry *)((nodePTR)->_data)).key)
#define ENTRY *(entry *)

BST BSTCreate(int KeyDataSize, int ValueDataSize, int (* KetIsEqual)(const void *, const void *),int (* KeyIsGreater)(const void * ,const void *) )
{
    BST new = {.KetIsEqual= KetIsEqual,
               .KeyIsGreater = KeyIsGreater,
               ._hot = NULL,
               ._KeyDataSize = KeyDataSize,
               ._ValueDataSize = ValueDataSize,
               ._BinTree._DataSize = sizeof(entry),
               ._BinTree._root = NULL,
               ._BinTree._size = 0 };
    return new;
}

BinNode *SearchIn(BST *_BST, BinNode *v, const void *KeyTarget)
{
    if (!v || _BST->KetIsEqual(KeyTarget, KeyPtr(v)))
        return v;
    _BST->_hot = v;
    return SearchIn(_BST, (_BST->KeyIsGreater(KeyPtr(v), KeyTarget) ? v->_lChild : v->_rChild), KeyTarget);
}

BinNode *BSTSearch(BST *_BST, const void *KeyTarget)
{
    _BST->_hot = NULL;
    return SearchIn(_BST, _BST->_BinTree._root, KeyTarget);
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
    BinNode *temp = BSTSearch(_BST, key);
    if (temp)
        return NULL;
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

BinNode * removeAt(BinNode *x, BinNode **hot)
{
    BinNode *w = x;
    BinNode *succ = NULL;
    if (!x->_lChild){
        succ = x = x->_rChild;
        w->_parent->_rChild = succ;
    }
    else if (!x->_rChild){
        succ = x = x->_lChild;
        w->_parent->_lChild = succ;
    }
    else
    {
        w = BNodeSucc(w);
        entry temp = ENTRY w->_data;
        ENTRY w->_data = ENTRY x->_data;
        ENTRY x->_data = temp;
        BinNode *u = w->_parent;
        if (u == x)
            u->_rChild = succ = w->_rChild;
        else
            u->_lChild = succ = w->_rChild;
    }
     *hot = w->_parent;
    if (succ)
        succ->_parent = *hot;
    EntryDestruct(w->_data);
    BNodeDestruct(w);
    return succ;
}

int BSTRemove(BST *_BST, const void *key)
{
    BinNode *node_2_remove = BSTSearch(_BST, key);
    if (!node_2_remove)
        return 0;
    removeAt(node_2_remove, &(_BST->_hot));
    _BST->_BinTree._size -= 1;
    BTreeUpdateHeightAbove(_BST->_hot);
    return 1;
}