add_library(LinkList list.c)
target_link_libraries(LinkList PRIVATE vector)
target_include_directories(LinkList INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})