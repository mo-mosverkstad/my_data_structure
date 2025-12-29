# Data Structure Implementations

A comprehensive collection of data structure implementations in multiple programming languages including C, Java, Python, and Rust.

## 📁 Repository Structure

```
my_data_structure/
├── c_data_structure/          # C implementations
├── java_data_structure/       # Java implementations  
├── python_data_structure/     # Python implementations
├── rust_data_structure/       # Rust implementations
└── ppt/                      # Documentation
```

## 🔧 C Data Structures

### Core Data Structures

| Data Structure | Files | Description |
|----------------|-------|-------------|
| **Array Queue** | `array_queue/` | Fixed-size circular queue implementation |
| **Binary Search Tree** | `binary_search_tree/` | Self-balancing binary search tree |
| **Hash Table** | `hashtable/` | Hash table with collision handling |
| **Heap** | `heap/` | Min-heap implementation |
| **Linked List** | `linked_list/` | Singly linked list with append/search |
| **Linked List Raw** | `linked_list_raw/` | Advanced linked list with sort/reverse |
| **Linked Queue** | `linked_queue/` | Queue using linked nodes |
| **Linked Stack** | `linked_stack/` | Stack using linked nodes |

### Sorting Algorithms

| Algorithm | File | Time Complexity |
|-----------|------|----------------|
| **Insertion Sort** | `sort/insertionsort.c` | O(n²) |
| **Merge Sort** | `sort/mergesort.c` | O(n log n) |
| **Quick Sort** | `sort/quicksort.c` | O(n log n) avg |
| **Selection Sort** | `sort/selectionsort.c` | O(n²) |

### Building and Testing

```bash
cd c_data_structure
mkdir build && cd build
cmake ..
make
ctest
```

Each data structure includes:
- Header file (`.h`) with API declarations
- Implementation file (`.c`) 
- Test file (`test_*.c`) with comprehensive test cases
- CMakeLists.txt for building

### Test Framework

Custom lightweight testing framework (`test_framework/test_framework.h`):
- `ASSERT_EQ(expected, actual)` - Assert equality
- `ASSERT_TRUE(condition)` - Assert condition is true
- `RUN_TEST(test_func)` - Execute test function
- `TEST_MAIN_END()` - Complete test suite

## ☕ Java Data Structures

### Binary Trees
- **BinarySortedTree.java** - Binary search tree implementation
- **Tree.java** - Generic tree interface
- **TreeNode.java** - Tree node structure
- **TreeTest.java** - Comprehensive test suite

### Sorting Algorithms
| Algorithm | File | Description |
|-----------|------|-------------|
| **Bubble Sort** | `bubbleSort/BubbleSortMain.java` | Simple comparison sort |
| **Exchange Sort** | `exchangeSort/ExchangeSortMain.java` | Selection-based sorting |
| **Heap Sort** | `heapSort/` | Heap-based sorting with Heap.java |
| **Merge Sort** | `mergeSort/MergeSortMain.java` | Divide and conquer sort |
| **Radix Sort** | `radixSort/RadixSortMain.java` | Non-comparison integer sort |
| **Tournament Sort** | `tournamentSort/` | Tournament tree sorting |

## 🐍 Python Data Structures

### Linear Data Structures
- **my_linear_list.py** - Array-based list implementation
- **my_linked_list.py** - Linked list with Python integration

### Queue and Stack
- **my_array_queue.py** - Array-based queue
- **my_queue.py** - Generic queue interface
- **my_stack.py** - Stack implementation

### Trees
- **my_binary_tree.py** - Binary tree operations
- **tree_binary_node.py** - Binary tree node structure

### Special Applications
- **class_my_rpn.py** - Reverse Polish Notation calculator

### Testing
Each Python module includes corresponding test files:
- `test_my_array_queue.py`
- `test_my_linear_list.py`
- `test_my_linked_list.py`
- `test_my_queue.py`
- `test_my_rpn.py`

## 🦀 Rust Data Structures

### Sorting
- **mergesort.rs** - Efficient merge sort implementation in Rust

## 🚀 Getting Started

### Prerequisites
- **C**: GCC/Clang compiler, CMake 3.10+
- **Java**: JDK 8+
- **Python**: Python 3.6+
- **Rust**: Rust 1.40+

### Quick Start

1. **Clone the repository**
```bash
git clone <repository-url>
cd my_data_structure
```

2. **Build C implementations**
```bash
cd c_data_structure
mkdir build && cd build
cmake ..
make
```

3. **Run tests**
```bash
ctest --verbose
```

4. **Compile Java programs**
```bash
cd java_data_structure/binaryTree
javac *.java
java BinaryTreeMain
```

5. **Run Python tests**
```bash
cd python_data_structure
python test_my_linear_list.py
```

## 📊 Features

### C Implementation Features
- **Memory Management**: Proper allocation/deallocation
- **Error Handling**: Null pointer checks and boundary validation
- **Generic Design**: Void pointers for type flexibility
- **Comprehensive Testing**: Full test coverage with edge cases
- **CMake Integration**: Modern build system

### Cross-Language Consistency
- Similar API designs across languages
- Consistent naming conventions
- Comparable functionality and performance

## 🧪 Testing

### Test Coverage
- **Unit Tests**: Individual function testing
- **Integration Tests**: Component interaction testing
- **Edge Cases**: Boundary conditions and error scenarios
- **Performance Tests**: Large dataset handling

### Test Categories
- Creation and destruction
- Basic operations (add, remove, search)
- Advanced operations (sort, reverse, merge)
- Empty structure handling
- Memory leak prevention

## 📈 Performance Characteristics

| Data Structure | Access | Search | Insertion | Deletion | Space |
|----------------|--------|--------|-----------|----------|-------|
| Array Queue | O(1) | O(n) | O(1) | O(1) | O(n) |
| Binary Search Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Hash Table | O(1) | O(1) | O(1) | O(1) | O(n) |
| Heap | O(1) | O(n) | O(log n) | O(log n) | O(n) |
| Linked List | O(n) | O(n) | O(1) | O(n) | O(n) |

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Add comprehensive tests
4. Ensure all tests pass
5. Submit a pull request

## 📝 License

This project is open source and available under the MIT License.

## 📚 Documentation

Additional documentation available in:
- `ppt/dataStructure.pptx` - Presentation slides
- Individual header files for API documentation
- Test files for usage examples