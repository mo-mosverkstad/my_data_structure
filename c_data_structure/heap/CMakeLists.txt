add_library(heap heap.c heap.h)

add_executable(test_heap test_heap.c)
target_link_libraries(test_heap heap)
target_include_directories(test_heap PRIVATE ../test_framework)

enable_testing()
add_test(NAME cmake_test_heap COMMAND test_heap)