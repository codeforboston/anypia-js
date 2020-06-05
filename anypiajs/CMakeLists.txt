cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE on)

project(anypiajs)

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
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
        # On Windows, you have to be specific to help cmake find boost 
        # because b2 has --layout=versioned by default.
        # https://stackoverflow.com/questions/31480059/how-to-link-boost-using-cmake-on-windows
        # https://stackoverflow.com/a/45546041/272018
        # also use -DBOOST_ROOT on Windows, not -DBOOST_INCLUDE_DIR
        # set (Boost_DEBUG ON)  
        set (Boost_COMPILER ${Boost_COMPILER} "-vc140")
        set (Boost_USE_STATIC_RUNTIME ON)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib)
    endif()

    # Create .html launcher as well
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_subdirectory(../oactobjs32/misc ${CMAKE_BINARY_DIR}/misc)
add_subdirectory(../oactobjs32/piadata ${CMAKE_BINARY_DIR}/piadata)
add_subdirectory(../oactobjs32/piaout ${CMAKE_BINARY_DIR}/piaout)
add_subdirectory(../oactobjs32/windows ${CMAKE_BINARY_DIR}/windows)

set(SOURCES
    "Main.cpp"
    "Application.cpp"
    "anypiatestdoc.cpp"
)

find_package(Boost 1.64.0 REQUIRED COMPONENTS date_time)

if(CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

set(EXPORTED_FUNCTIONS "-s EXPORTED_FUNCTIONS=\"[\
	'_GetAge',\
	'_GetCalc',\
	'_GetYears',\
	'_InitalizeApplication']\"")
	
set(EXPORTED_RUNTIME_METHODS "-s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall', 'cwrap']\"")

add_compile_definitions("WEB_ASSEMBLY")

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS " ${EXPORTED_FUNCTIONS} ${EXPORTED_RUNTIME_METHODS}")
#set(EMCC_CFLAGS "${EMCC_CFLAGS} ")
#set(EMCC_CFLAGS "${EMCC_CFLAGS} -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']")


#if(NOT DEFINED ANYPIATEST)
#    add_compile_definitions("ANYPIAB")
#endif(NOT DEFINED ANYPIATEST)
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
