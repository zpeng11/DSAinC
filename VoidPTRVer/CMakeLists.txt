cmake_minimum_required(VERSION 3.1)

project(DSAinC)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(vector)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(LinkList)

add_executable(DSAinC main.c)
target_link_libraries(DSAinC PUBLIC vector)
target_link_libraries(DSAinC PUBLIC stack)
target_link_libraries(DSAinC PUBLIC LinkList)
target_link_libraries(DSAinC PUBLIC queue)

