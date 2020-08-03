add_library(BST BST.c)
target_include_directories(BST INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(BST PUBLIC BinNode)
target_link_libraries(BST PUBLIC BinTree)