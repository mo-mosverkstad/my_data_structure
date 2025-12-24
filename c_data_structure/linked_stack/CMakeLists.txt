add_library(linked_stack linked_stack.c linked_stack.h)

add_executable(test_linked_stack test_linked_stack.c)
target_link_libraries(test_linked_stack linked_stack)
target_include_directories(test_linked_stack PRIVATE ../test_framework)

enable_testing()
add_test(NAME cmake_test_linked_stack COMMAND test_linked_stack)