cmake_minimum_required(VERSION 3.1.0)
project(r-type)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Conan configuration

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Build the server and the client

link_libraries(${CONAN_LIBS})
add_subdirectory(engine)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(draft)
