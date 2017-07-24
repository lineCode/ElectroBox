cmake_minimum_required(VERSION 3.4.1)



file(GLOB_RECURSE P_SOURCES "src/main/cpp/src/*.cpp")
file(GLOB_RECURSE P_HEADERS "src/main/cpp/include/*.h")

set (P_INCLUDE_DIRS "")
foreach (_headerFile ${P_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND P_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES P_INCLUDE_DIRS)


include_directories(${P_INCLUDE_DIRS})
add_library(native-lib SHARED ${P_SOURCES})
find_library(log-lib log)

target_link_libraries(native-lib
    ${log-lib}
    -lGLESv2
)