cmake_minimum_required(VERSION 3.9)
project(hough)

set(CMAKE_CXX_STANDARD 14)

#set(OpenCV_DIR "C:/Program Files/opencv/build")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(houghtransform Hough.cpp Hough.hpp main.cpp)
target_link_libraries(houghtransform ${OpenCV_LIBS})

