cmake_minimum_required(VERSION 3.10)

project(anypiab)

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

add_executable(${PROJECT_NAME} ${SOURCES})

if(NOT DEFINED ANYPIATEST)
    add_compile_definitions("ANYPIAB")
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
