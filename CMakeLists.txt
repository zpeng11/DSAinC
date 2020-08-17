cmake_minimum_required(VERSION 3.1)

project(DSAinC)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(vector)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(LinkList)
add_subdirectory(BinTree)
add_subdirectory(BST)
add_subdirectory(AVL)
add_subdirectory(RBTree)
add_subdirectory(heap)
list(APPEND libs vector)
list(APPEND libs stack)
list(APPEND libs queue)
list(APPEND libs LinkList)
list(APPEND libs BinTree)
list(APPEND libs BinNode)
list(APPEND libs BST)
list(APPEND libs AVL)
list(APPEND libs RBTree)
list(APPEND libs heap)



add_library(DSAinC DSA.c)
add_executable(DSA DSA.c)
target_link_libraries(DSA PUBLIC ${libs})
target_link_libraries(DSAinC PUBLIC ${libs})

