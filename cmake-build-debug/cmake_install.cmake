# Install script for directory: /home/talion/Documents/School/EPITECH/tek3/B5/Cpp/R-type/B-CPP-501-LYN-5-1-rtype-hugo.perinazzo

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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/talion/Documents/School/EPITECH/tek3/B5/Cpp/R-type/B-CPP-501-LYN-5-1-rtype-hugo.perinazzo/cmake-build-debug/engine/cmake_install.cmake")
  include("/home/talion/Documents/School/EPITECH/tek3/B5/Cpp/R-type/B-CPP-501-LYN-5-1-rtype-hugo.perinazzo/cmake-build-debug/server/cmake_install.cmake")
  include("/home/talion/Documents/School/EPITECH/tek3/B5/Cpp/R-type/B-CPP-501-LYN-5-1-rtype-hugo.perinazzo/cmake-build-debug/client/cmake_install.cmake")
  include("/home/talion/Documents/School/EPITECH/tek3/B5/Cpp/R-type/B-CPP-501-LYN-5-1-rtype-hugo.perinazzo/cmake-build-debug/draft/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/talion/Documents/School/EPITECH/tek3/B5/Cpp/R-type/B-CPP-501-LYN-5-1-rtype-hugo.perinazzo/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")