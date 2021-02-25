cmake_minimum_required(VERSION 3.17)
project(arithmetic_coding)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtkmm-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(arithmetic_coding main.cpp src/FileReader.cpp include/FileReader.h src/Encoder.cpp include/Encoder.h src/Decoder.cpp include/Decoder.h src/FileWriter.cpp include/FileWriter.h)

target_link_libraries(arithmetic_coding ${GTK3_LIBRARIES})