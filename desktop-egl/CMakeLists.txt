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

add_library(libChakraCore SHARED IMPORTED)
set_property(TARGET libChakraCore PROPERTY IMPORTED_LOCATION libChakraCore.so)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g")
set( ADDITIONAL_LIBS
        -ldl
        -pthread
        -lrt
)

include_directories(${INCLUDE_DIRS})

add_executable(canvas-native ${SOURCES}  ${SOURCES_C})
target_link_libraries(canvas-native ${ADDITIONAL_LIBS} libChakraCore)