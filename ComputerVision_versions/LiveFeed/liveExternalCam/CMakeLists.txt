cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(testTilProjekt)

include_directories("/usr/include/opencv4/")
link_directories("/usr/lib/x86_64-linux-gnu/")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(PkgConfig REQUIRED)
pkg_search_module(GST REQUIRED gstreamer-1.0>=1.4
    gstreamer-sdp-1.0>=1.4
    gstreamer-video-1.0>=1.4
    gstreamer-app-1.0>=1.4)
include_directories( ${GST_INCLUDE_DIRS})

add_executable(myExe main.cpp
    )

target_link_libraries(myExe opencv_core opencv_highgui opencv_imgcodecs)
target_link_libraries(myExe ${OpenCV_LIBS} )

target_link_libraries(myExe ${GST_LIBRARIES})
