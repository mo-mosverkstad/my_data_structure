add_library(hashtable hashtable.c hashtable.h)

add_executable(test_hashtable test_hashtable.c)
target_link_libraries(test_hashtable hashtable)
target_include_directories(test_hashtable PRIVATE ../test_framework)

enable_testing()
add_test(NAME cmake_test_hashtable COMMAND test_hashtable)