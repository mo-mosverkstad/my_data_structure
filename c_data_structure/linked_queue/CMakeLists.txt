add_library(linked_queue linked_queue.c linked_queue.h)

add_executable(test_linked_queue test_linked_queue.c)
target_link_libraries(test_linked_queue linked_queue)
target_include_directories(test_linked_queue PRIVATE ../test_framework)

enable_testing()
add_test(NAME cmake_test_linked_queue COMMAND test_linked_queue)