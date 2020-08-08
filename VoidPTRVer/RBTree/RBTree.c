#include "RBTree.h"

#define KeyPtr(nodePTR) ((*(entry *)((nodePTR)->_data)).key)
#define ENTRY *(entry *)
#define Key(nodePTR) *(int *)((*(entry *)((nodePTR)->_data)).key)
#define IsLChild(nodePTR) ((nodePTR)->_parent->_lChild == (nodePTR))
#define IsRChild(nodePTR) ((nodePTR)->_parent->_rChild == (nodePTR))
#define lc(BNodePTR) ((BNodePTR)->_lChild)
#define rc(BNodePTR) ((BNodePTR)->_rChild)
#define stature(p) ((p) ? (p)->_height : -1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define tallerChild(nodePTR) (((stature(lc(nodePTR))) > (stature(rc(nodePTR)))) ? lc(nodePTR) : rc(nodePTR))
#define FromParentTo(nodePTR) ((!((nodePTR)->_parent)) ? (&(_RBT->_BinTree._root)) : ((lc((nodePTR)->_parent) == (nodePTR)) ? (&(lc((nodePTR)->_parent))) : (&(rc((nodePTR)->_parent)))))
#define isRoot(nodePTR) (_RBT->_height == (nodePTR))
#define isBlack(nodePTR) ((nodePTR)->_color)
#define isRed(nodePTR) (!((nodePTR)->_color))
#define getUncle(nodePTR) (((lc(nodePTR)->_parent) == (nodePTR)) ? (rc((nodePTR)->_parent)) : (lc((nodePTR)->_parent)))

int RBTUpdateHeight(BinNode *_node)
{
    _node->_height = max(stature(lc(_node)), stature(rc(_node)));
    if (isBlack(_node))
        _node->_height++;
    return _node->_height;
}

BinNode *RBTInsert(RBT *_RBT, const void *key, const void *value)
{
    BinNode **x = BSTSearch(_RBT, key);
    if (*x)
        return *x;
    entry NewEntry = EntryCreate(key, _RBT->_KeyDataSize, value, _RBT->_ValueDataSize);
    *x = BNodeCreate(&NewEntry, sizeof(entry));
    (*x)->_parent = _RBT->_hot;
    (_RBT->_BinTree._size) += 1;
    solveDoubleRed(_RBT, *x);
    return (*x) ? (*x) : _RBT->_hot->_parent;
}

void solveDoubleRed(RBT *_RBT, BinNode *x)
{
    while (1)
    {
        BinNode *p = x->_parent;
        BinNode *g = (p) ? p->_parent : NULL;
        if (x == _RBT->_BinTree._root) //root
        {
            x->_color = B;
            RBTUpdateHeight(x);
            break;
        }
        else if (p && isBlack(p)) //red-black
        {
            RBTUpdateHeight(x);
            //do nothing
            break;
        }
        else if (p && isRed(p)) //double Red
        {
            BinNode *u = getUncle(p);
            if (!u || isBlack(u)) //RR with black uncle
            {
                BinNode **fromParentTog = FromParentTo(g);
                *fromParentTog = BSTRotateAt(x, RBTUpdateHeight);
                (*fromParentTog)->_color = B;
                (*fromParentTog)->_rChild->_color = (*fromParentTog)->_lChild->_color = R;
                break;
            }
            else //RR with Red uncle, change color and go to next iteration
            {
                g->_color = R;
                p->_color = u->_color = B;
                x->_color = R;
                x = g;
            }
        }
    }
}

int RBTRemove(RBT *_RBT, const void *key)
{
    BinNode **x = BSTSearch(_RBT, key);
    if (!(*x))
        return 0;
    int xColor ;
    BinNode * r = BSTRemoveAt(x,&(_RBT->_hot),&xColor);
    (_RBT->_BinTree._size) -=1;
    solveDoubleBlack(_RBT, xColor, r);
    return 1;
}

void solveDoubleBlack(RBT *_RBT, int xColor, BinNode *r)
{
    while (1)
    {
        if(xColor != r->_color)
        {
            r->_color = B;
            RBTUpdateHeight(r);
            break;
        }
        else //BB
        {
            BinNode * p = r->_parent;
            if(!p)//replacement happens at root
                break;
            BinNode * s = (IsLChild(r))?rc(p):lc(p);//sibling of r must exits and has at least two Black height
            if(isBlack(s))//sibling is black
            {
                BinNode * t = isRed(lc(s))? lc(s) : (isRed(rc(s))? rc(s) : NULL);//find a red son of s 
                if(t)//case BB-1
                {
                    int pColor = p->_color;
                    BinNode ** FromParentToP = FromParentTo(p);
                    *FromParentToP = BSTRotateAt(t, RBTUpdateHeight);
                    lc(*FromParentToP)->_color = rc(*FromParentToP)->_color = B;
                    RBTUpdateHeight(lc(*FromParentToP));
                    RBTUpdateHeight(rc(*FromParentToP));
                    (*FromParentToP)->_color = R;
                    RBTUpdateHeight(*FromParentToP);
                    break;
                }
                else // there is no red son of s
                {
                    if(isRed(p))//BB-2R, p is red
                    {
                        p->_color = B;
                        s->_color = R;
                        RBTUpdateHeight(s);
                        RBTUpdateHeight(p);
                        break;
                    }
                    else //BB-2B, p is black
                    {
                        s->_color = R;
                        RBTUpdateHeight(s);
                        RBTUpdateHeight(p);
                        r = p;
                        //go to next iteration
                    }
                }
            }
            else //BB-3, sibling is red
            {
                 *FromParentTo(p) = s;
                 s->_parent = p ->_parent;
                 if(IsLChild(r))
                 {
                     p->_rChild = s->_lChild;
                     p->_rChild->_parent = p;
                     p->_parent = s;
                     s->_lChild = p;
                 }
                 else
                 {
                     p->_lChild = s->_rChild;
                     p->_lChild->_parent = p;
                     p->_parent = s;
                     s->_rChild = p;
                 }
            }//go to next iteration
        }
        //end of one iteration 
    }
    //end of loop    
}