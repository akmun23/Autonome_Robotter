cmake_minimum_required(VERSION 3.5.0)
project(Project_GUI VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(ur_rtde REQUIRED)
find_package(Qt5Sql REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("/usr/include/opencv4/")
link_directories("/usr/lib/x86_64-linux-gnu/")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories("/usr/include/opencv4/opencv2")

add_executable(Project_GUI main.cpp
    boardUpdate.h BoardUpdate.cpp
    matrix.h matrix.cpp
    alphabeta.h alphabeta.cpp
    validmoves.h validmoves.cpp
    vision.h vision.cpp
    robot.h robot.cpp
    AtmegaCom.h AtmegaCom.cpp
    DrawFunctions.h
    GameFunctions.h)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
target_link_libraries(Project_GUI PRIVATE ur_rtde::rtde Qt5::Core Qt5::Sql opencv_core opencv_highgui opencv_imgcodecs ${OpenCV_LIBS})
