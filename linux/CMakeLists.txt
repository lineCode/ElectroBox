cmake_minimum_required(VERSION 3.7)
project(cobalt-core)

set(CMAKE_CXX_STANDARD 11)
set(ARCH_DIR "linux64")

file(GLOB_RECURSE SOURCES "../src/*.cpp")
file(GLOB_RECURSE HEADERS "../include/*.h")


set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -m64")

# Add V8 Libs for Linux

ADD_LIBRARY(libicuuc SHARED IMPORTED)
SET_TARGET_PROPERTIES(libicuuc PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libicuuc.so)

ADD_LIBRARY(libicui18n SHARED IMPORTED)
SET_TARGET_PROPERTIES(libicui18n PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libicui18n.so)

ADD_LIBRARY(libv8 SHARED IMPORTED)
SET_TARGET_PROPERTIES(libv8 PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libv8.so)

ADD_LIBRARY(libv8_libbase SHARED IMPORTED)
SET_TARGET_PROPERTIES(libv8_libbase PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libv8_libbase.so)

ADD_LIBRARY(libv8_libplatform SHARED IMPORTED)
SET_TARGET_PROPERTIES(libv8_libplatform PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libv8_libplatform.so)

# -----

include_directories(${INCLUDE_DIRS})
add_executable(cobalt-core ${SOURCES})
target_link_libraries(cobalt-core
        libicuuc
        libicui18n
        libv8
        libv8_libbase
        libv8_libplatform
        -lrt
        -ldl
)