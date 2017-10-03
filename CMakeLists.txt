cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(lab1)

add_executable(lab1 src/main.cpp src/bus.cpp src/cpu.cpp src/timer.cpp src/oc.cpp)

add_library(systemc SHARED IMPORTED)

set_target_properties(systemc PROPERTIES
  IMPORTED_LOCATION "/usr/local/systemc-2.3.1/lib-linux64/libsystemc.so"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/local/systemc-2.3.1/include"
)

set_target_properties(lab1 PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(lab1 m systemc)