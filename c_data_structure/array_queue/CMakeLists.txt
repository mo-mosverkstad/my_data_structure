add_library(array_queue array_queue.c array_queue.h)

add_executable(test_array_queue test_array_queue.c)
target_link_libraries(test_array_queue array_queue)
target_include_directories(test_array_queue PRIVATE ../test_framework)

enable_testing()
add_test(NAME cmake_test_array_queue COMMAND test_array_queue)