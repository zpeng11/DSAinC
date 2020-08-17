add_library(stack stack.c)
target_link_libraries(stack PUBLIC vector)


target_include_directories(stack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})