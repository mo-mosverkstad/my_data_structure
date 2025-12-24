add_library(linked_list linked_list.c linked_list.h)

add_executable(test_linked_list test_linked_list.c)
target_link_libraries(test_linked_list linked_list)
target_include_directories(test_linked_list PRIVATE ../test_framework)

enable_testing()
add_test(NAME cmake_test_linked_list COMMAND test_linked_list)