add_library(queue queue.c)
target_link_libraries(queue PUBLIC LinkList)
target_include_directories(queue INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")