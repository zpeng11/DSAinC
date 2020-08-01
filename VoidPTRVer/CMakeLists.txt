cmake_minimum_required(VERSION 3.1)

project(DSAinC)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(vector)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(LinkList)
add_subdirectory(BinTree)
list(APPEND libs vector)
list(APPEND libs stack)
list(APPEND libs queue)
list(APPEND libs LinkList)
list(APPEND libs BinTree)


add_library(DSAinC DSA.c)
add_executable(DSA DSA.c)
target_link_libraries(DSA PUBLIC ${libs})
target_link_libraries(DSAinC PUBLIC ${libs})

