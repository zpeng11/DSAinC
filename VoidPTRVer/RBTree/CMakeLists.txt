add_library(RBTree RBTree.c)
target_include_directories(RBTree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(RBTree PUBLIC BST)