#ifndef AVL_H
#define AVL_H
#include "BST.h"


#define AVL BST
#define AVLCreate BSTCreate
#define AVLDestruct BSTDestruct
#define AVLSearch BSTSearch
BinNode * AVLInseart(AVL *_BST, const void * Key, const void * value);
int AVLRemove(AVL * _BST, const void * key);
#endif /*AVL_H*/