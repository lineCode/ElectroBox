cmake_minimum_required(VERSION 3.7)
project(canvas-native)

add_definitions(-DDEBUG)


file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE SOURCES_C "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

add_library(libv8 SHARED IMPORTED)
add_library(libv8_libbase SHARED IMPORTED)
add_library(libv8_libplatform SHARED IMPORTED)
add_library(libicuuc SHARED IMPORTED)
add_library(libicui18n SHARED IMPORTED)

set_property(TARGET libv8 PROPERTY IMPORTED_LOCATION libv8.so)
set_property(TARGET libv8_libbase PROPERTY IMPORTED_LOCATION libv8_libbase.so)
set_property(TARGET libv8_libplatform PROPERTY IMPORTED_LOCATION libv8_libplatform.so)
set_property(TARGET libicuuc PROPERTY IMPORTED_LOCATION libicuuc.so)
set_property(TARGET libicui18n PROPERTY IMPORTED_LOCATION libicui18n.so)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g")
set( ADDITIONAL_LIBS
        -ldl
        -pthread
        -lrt
)

include_directories(${INCLUDE_DIRS})

add_executable(canvas-native ${SOURCES}  ${SOURCES_C})
target_link_libraries(canvas-native ${ADDITIONAL_LIBS} libv8 libv8_libbase libv8_libplatform libicuuc libicui18n)