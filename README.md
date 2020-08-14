# DSAinC
Useful Data Structure and Algorithm implement in C

As planned, this project will implement Data Structure like vector, Btree, RBTree, set, map and so on with related algorithms.
There are two version of implementation differ in the way they treat data type stored in the container:
1. Macro implement, which encapsulates data type by macro, it is easier to use for relatively small project(user friendly). The drawback is that every copy of the library can only handle one datatype. 
2. (void *)implement, which provides interface only with (void *), in other words, it only works as memory manager, unsensity to data type. It is helpful for relatively big project but hard to use (even for me the writer LOL)

