cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)

find_package(ur_rtde REQUIRED)
find_package(Qt5Sql REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp
    validMoves.h
    boardUpdate.h
    robotMove.h
    AtmegaCom.h
    CheckersDatabase.h
    FunktionerTilDatabase.cpp)

target_link_libraries(main PRIVATE ur_rtde::rtde Qt5::Core Qt5::Sql)
