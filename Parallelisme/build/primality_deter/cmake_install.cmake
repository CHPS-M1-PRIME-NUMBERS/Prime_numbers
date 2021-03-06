# Install script for directory: /home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/primality_deter

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE STATIC_LIBRARY FILES "/home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/build/primality_deter/libprimality_deter.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/primality_deter/AKS.hpp"
    "/home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/primality_deter/eratosthene.hpp"
    "/home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/primality_deter/CPolyMod.hpp"
    "/home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/primality_deter/euclide.hpp"
    "/home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/primality_deter/facteurs.hpp"
    "/home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/primality_deter/memory_bound.hpp"
    "/home/jean-didier/Bureau/Projet/Prime_numbers/Parallelisme/primality_deter/pocklington.hpp"
    )
endif()

