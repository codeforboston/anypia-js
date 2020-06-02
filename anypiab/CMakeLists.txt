cmake_minimum_required(VERSION 3.10)

project(anypiab)

if(CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    # CMake's Emscripten settings search for everything under
    # the toolchain prefix, this breaks Boost find_package.
    # Turn this off just around the Boost find_package.
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)

    # On macOS Boost libraries are built as .bc and .dylib,
    # but CMake Emscripten's settings for .so and .a by default
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .bc .dylib)
    endif()

    # Create .html launcher as well
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_subdirectory(../oactobjs32/misc ${CMAKE_BINARY_DIR}/misc)
add_subdirectory(../oactobjs32/piadata ${CMAKE_BINARY_DIR}/piadata)
add_subdirectory(../oactobjs32/piaout ${CMAKE_BINARY_DIR}/piaout)
add_subdirectory(../oactobjs32/windows ${CMAKE_BINARY_DIR}/windows)

set(SOURCES
    "anypiab.cpp"
    "anypiabdoc.cpp"
    "anypiatestdoc.cpp"
)

find_package(Boost 1.64.0 REQUIRED COMPONENTS date_time)

if(CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

if(NOT DEFINED ANYPIATEST)
    add_compile_definitions("ANYPIAB" "DETAILS")
endif(NOT DEFINED ANYPIATEST)

# On Linux, the order of these libraries matters!
target_link_libraries(${PROJECT_NAME} PUBLIC
    piadata
    piaout
    misc
    windows
    Boost::date_time
)
target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/../oactobjs32"
    ${Boost_INCLUDE_DIRS}
)
