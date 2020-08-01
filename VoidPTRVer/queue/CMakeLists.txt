add_library(queue queue.c)
target_link_libraries(queue PRIVATE LinkList)
target_link_directories(queue INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")