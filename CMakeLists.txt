cmake_minimum_required(VERSION 3.15)
project(PathFinding LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 优化编译选项
add_compile_options(-O3 -march=native -ffast-math)
add_library(PathFind SHARED
    src/core/Grid.cpp
    src/core/Heap.cpp
    src/core/Heuristic.cpp
    src/core/Node.cpp
    src/core/Util.cpp
    src/finders/AStar.cpp
    src/finders/BestFirst.cpp
    src/finders/BreadthFirst.cpp
    src/finders/Dijkstra.cpp
    src/finders/IDAStar.cpp
    src/finders/JPFAlways.cpp
    src/finders/JPFIfAtMostOneObstacle.cpp
    src/finders/JPFNoObstacles.cpp
    src/finders/JPFNever.cpp
    src/finders/JumpPointFinder.cpp
    src/finders/JumpPointFinderBase.cpp
    src/PathFind.cpp
)
set_target_properties(PathFind PROPERTIES VERSION 1.0.0 SOVERSION 1)
target_include_directories(PathFind PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(PathFindTest test/test.cpp)
target_link_libraries(PathFindTest PathFind)

add_executable(PathFindTest2 test/test2.cpp)
target_link_libraries(PathFindTest2 PathFind)