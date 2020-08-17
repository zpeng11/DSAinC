#ifndef AVL_H
#define AVL_H
#include "BST.h"


#define AVL BST
#define AVLCreate BSTCreate
#define AVLDestruct BSTDestruct
#define AVLSearch BSTSearch
BinNode * AVLInseart(AVL *_BST, const void * Key, const void * value);//overloaded insert
int AVLRemove(AVL * _BST, const void * key);//overloaded remove
#endif /*AVL_H*/