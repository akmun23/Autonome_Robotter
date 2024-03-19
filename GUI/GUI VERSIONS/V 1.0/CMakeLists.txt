cmake_minimum_required(VERSION 3.5.0)
project(Project_GUI VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Project_GUI main.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( Project_GUI ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
