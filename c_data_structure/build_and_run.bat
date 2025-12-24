@echo off
mkdir build 2>nul
cd build
cmake ..
cmake --build .
echo.
echo Running tests:
heap\test_heap.exe