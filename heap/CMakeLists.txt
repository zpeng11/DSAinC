add_library(heap heap.c)
target_link_libraries(heap PUBLIC vector)


target_link_libraries(heap PUBLIC BST)
target_include_directories(heap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})