cmake_minimum_required(VERSION 3.25)
project(line_detection)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(line_detection main.cpp)
target_link_libraries(line_detection ${OpenCV_LIBS})
