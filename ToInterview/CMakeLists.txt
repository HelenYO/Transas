cmake_minimum_required(VERSION 3.15)
project(ToInterview)

set(CMAKE_CXX_STANDARD 20)

add_executable(ToInterview main.cpp Request.h Stopper.h Worker.h)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS chrono filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(ToInterview ${Boost_LIBRARIES})