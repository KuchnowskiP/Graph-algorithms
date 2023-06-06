cmake_minimum_required(VERSION 3.25)
project(untitled3)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(untitled3 main.cpp ShortestPath.cpp ShortestPath.h MST.cpp MST.h TimeCounter.h TimeCounter.cpp ReadNGenerate.h ReadNGenerate.cpp Matrix.h Matrix.cpp AdjacencyLists.cpp AdjacencyLists.h DLNeighbourList.h DLNeighbourList.cpp PriorityQueue.cpp PriorityQueue.h)
