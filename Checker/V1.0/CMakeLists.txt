cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)

find_package(ur_rtde REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp
    validMoves.h
    boardUpdate.h
    robotMove.h
    AtmegaCom.h)

target_link_libraries(main PRIVATE ur_rtde::rtde)

include(GNUInstallDirs)
install(TARGETS main
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
