add_library(splay splay.c)
target_include_directories(splay INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(splay BST)