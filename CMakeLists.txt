cmake_minimum_required(VERSION 3.0.0)
project(SkipList)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/sanitizers-cmake/cmake" ${CMAKE_MODULE_PATH})
set(SANITIZE_ADDRESS TRUE)
set(CMAKE_CXX_STANDARD 17)
find_package(Sanitizers)

add_executable(
    SortingAlgorithms

    main.cpp

    SkipList.cpp
)

add_sanitizers(SkipList)