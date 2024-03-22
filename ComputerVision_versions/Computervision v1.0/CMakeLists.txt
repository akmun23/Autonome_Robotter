cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(calibrationtest)

include_directories("/usr/include/opencv4/")
link_directories("/usr/lib/x86_64-linux-gnu/")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(myExe main.cpp
    qa.hpp
    )

target_link_libraries(myExe opencv_core opencv_highgui opencv_imgcodecs)
target_link_libraries( myExe ${OpenCV_LIBS} )
