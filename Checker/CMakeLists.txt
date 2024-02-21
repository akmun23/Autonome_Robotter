cmake_minimum_required(VERSION 3.5)

project(Checker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Checker main.cpp
    boardUpdate.h
    playerInput.h
    validMoves.h
)

include(GNUInstallDirs)
install(TARGETS Checker
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
