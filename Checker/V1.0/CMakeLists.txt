cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)

find_package(ur_rtde REQUIRED)
find_package(Qt5Sql REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("/usr/include/opencv4/")
link_directories("/usr/lib/x86_64-linux-gnu/")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(main main.cpp
    validMoves.h
    boardUpdate.h
    robotMove.h
    AtmegaCom.h
    CheckersDatabase.h

    FunktionerTilDatabase.cpp
    computerVision.h
    qa.hpp
    matrix.cpp
    matrix.h
    mainfunctions.h mainfunctions.cpp
    ValidMoves.cpp
    Atmega.cpp
    BoardUpdate.cpp
    ComputerVision.cpp


    robotMove.cpp
)

target_link_libraries(main PRIVATE ur_rtde::rtde Qt5::Core Qt5::Sql opencv_core opencv_highgui opencv_imgcodecs ${OpenCV_LIBS})
