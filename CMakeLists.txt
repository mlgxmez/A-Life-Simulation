cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

#set(CXX_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

project(ALifeSimulation)

add_executable(ALifeSimulation src/main.cpp src/Activity.cpp src/Person.cpp)
