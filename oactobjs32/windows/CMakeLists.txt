cmake_minimum_required(VERSION 3.10)

project(windows)

set(SOURCES
    "BitAnnualBase.cpp"
)

find_package(Boost 1.64.0 REQUIRED COMPONENTS date_time)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/../include"
    ${Boost_INCLUDE_DIRS}
)
