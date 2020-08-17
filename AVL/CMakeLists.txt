add_library(AVL AVL.c)
target_include_directories(AVL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AVL BST)