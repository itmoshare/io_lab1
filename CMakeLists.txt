cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(lab1)

add_executable(lab1 src/main.cpp src/bus.cpp src/cpu.cpp src/timer.cpp src/oc.cpp)

add_library(systemc SHARED IMPORTED)

set_target_properties(systemc PROPERTIES
  IMPORTED_LOCATION "/usr/local/systemc231/lib-linux64/libsystemc.so"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/local/systemc231/include"
)

set_target_properties(lab1 PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

target_link_libraries(lab1 m systemc)
