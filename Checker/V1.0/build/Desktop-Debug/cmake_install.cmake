<<<<<<< HEAD:GUI/GUI VERSIONS/V3.5/build/cmake_install.cmake
# Install script for directory: /home/mads-hyrup/Documents/GitHub/Autonome_Robotter/GUI/GUI VERSIONS/V3.5
=======
# Install script for directory: /home/pascal/Documents/GitHub/Autonome_Robotter/Checker/V1.0
>>>>>>> evolutionAI:Checker/V1.0/build/Desktop-Debug/cmake_install.cmake

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump-16")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD:GUI/GUI VERSIONS/V3.5/build/cmake_install.cmake
file(WRITE "/home/mads-hyrup/Documents/GitHub/Autonome_Robotter/GUI/GUI VERSIONS/V3.5/build/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/home/pascal/Documents/GitHub/Autonome_Robotter/Checker/V1.0/build/Desktop-Debug/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> evolutionAI:Checker/V1.0/build/Desktop-Debug/cmake_install.cmake
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
