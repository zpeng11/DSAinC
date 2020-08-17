# DSAinC
Useful Data Structure and Algorithm implement in C

This project will implement Data Structure like vector, linklist, RBTree, heap and so on with related algorithms.

In order to deal with different data store in the contain I used (void *) to manage space, which means whenever a new container is created, data size should be decleared.

When the user wants to store data into the container, one should make data into location value and pass its pointer to the container. Then the container would copy and store data. 

When the user wants to get data from the container, the container would return a void ptr to data space in the container, it is the user's responsibity to get real useful data from this ptr.
