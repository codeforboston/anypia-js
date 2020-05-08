cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project(anypiab C CXX)
#set(CMAKE_VERBOSE_MAKEFILE ON)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
#TDK: doesn't apply for emscripten and -G "NMake Makefile"
##########
#if(NOT CMAKE_VS_PLATFORM_NAME)
#    set(CMAKE_VS_PLATFORM_NAME "x64")
#endif()
#message("${CMAKE_VS_PLATFORM_NAME} architecture in use")
#
#if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"))
#    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
#endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "anypiabDebug"
    "anypiabRelease"
    "anypiacDebug"
    "anypiacRelease"
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_ANYPIABDEBUG "")
    set(CMAKE_C_FLAGS_ANYPIABRELEASE "")
    set(CMAKE_C_FLAGS_ANYPIACDEBUG "")
    set(CMAKE_C_FLAGS_ANYPIACRELEASE "")
    set(CMAKE_C_FLAGS_DEBUG "")
    set(CMAKE_C_FLAGS_RELEASE "")
    set(CMAKE_CXX_FLAGS "/EHsc")
    set(CMAKE_CXX_FLAGS_ANYPIABDEBUG "")
    set(CMAKE_CXX_FLAGS_ANYPIABRELEASE "")
    set(CMAKE_CXX_FLAGS_ANYPIACDEBUG "")
    set(CMAKE_CXX_FLAGS_ANYPIACRELEASE "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_ANYPIABDEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_ANYPIABDEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_ANYPIABDEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_ANYPIABDEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_ANYPIABRELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_ANYPIABRELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_ANYPIABRELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_ANYPIABRELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_ANYPIACDEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_ANYPIACDEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_ANYPIACDEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_ANYPIACDEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_ANYPIACRELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_ANYPIACRELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_ANYPIACRELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_ANYPIACRELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################
add_subdirectory(../oactobjs32/misc ${CMAKE_BINARY_DIR}/misc)
add_subdirectory(../oactobjs32/piadata ${CMAKE_BINARY_DIR}/piadata)
add_subdirectory(../oactobjs32/piaout ${CMAKE_BINARY_DIR}/piaout)
add_subdirectory(../oactobjs32/windows ${CMAKE_BINARY_DIR}/windows)



























project(anypiab CXX)

################################################################################
# Source groups
################################################################################
set(Headers
    "anypiabdoc.h"
    "anypiatestdoc.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "anypiab.cpp"
    "anypiabdoc.cpp"
    "anypiatestdoc.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${no_group_source_files}
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

############
# TDK: https://stackoverflow.com/questions/15724357/using-boost-with-emscripten
############
#set_target_properties (${PROJECT_NAME} PROPERTIES 
#COMPILE_FLAGS "-s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0" LINK_FLAGS "--bind --emrun -s TOTAL_MEMORY=500MB -s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0"
#)

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_ANYPIABDEBUG   "anypiab"
    TARGET_NAME_ANYPIABRELEASE "anypiab"
    TARGET_NAME_ANYPIACDEBUG   "anypiac"
    TARGET_NAME_ANYPIACRELEASE "anypiac"
    TARGET_NAME_DEBUG          "anypiab"
    TARGET_NAME_RELEASE        "anypiab"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_ANYPIABDEBUG   "$<CONFIG>"
    OUTPUT_DIRECTORY_ANYPIABRELEASE "$<CONFIG>"
    OUTPUT_DIRECTORY_ANYPIACDEBUG   "$<CONFIG>"
    OUTPUT_DIRECTORY_ANYPIACRELEASE "$<CONFIG>"
    OUTPUT_DIRECTORY_DEBUG          "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_RELEASE        "${CMAKE_CURRENT_SOURCE_DIR}/Release"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PDB_OUTPUT_DIRECTORY_ANYPIABDEBUG   "${OUTPUT_DIRECTORY}"
    PDB_OUTPUT_DIRECTORY_ANYPIACDEBUG   "${OUTPUT_DIRECTORY}"
    PDB_OUTPUT_DIRECTORY_DEBUG          "${OUTPUT_DIRECTORY}"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../oactobjs32;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../oactobjs32/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../oactobjs32/windows;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../oactobjs32/boost_1_64_0"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:anypiabDebug>:"
        "_DEBUG;"
        "ONEBIGFILE"
    ">"
    "$<$<CONFIG:anypiabRelease>:"
        "NDEBUG;"
        "ONEBIGFILE"
    ">"
    "$<$<CONFIG:anypiacDebug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:anypiacRelease>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "ONEBIGFILE"
    ">"
    "WIN32;"
    "_CONSOLE;"
    "ANYPIAB;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:anypiabDebug>:
            /Gm;
            /Od;
            /RTC1;
            /MTd;
            /ZI
        >
        $<$<CONFIG:anypiabRelease>:
            /MT;
            /Zi
        >
        $<$<CONFIG:anypiacDebug>:
            /Gm;
            /Od;
            /RTC1;
            /MTd;
            /ZI
        >
        $<$<CONFIG:anypiacRelease>:
            /MT;
            /Zi
        >
        $<$<CONFIG:Debug>:
            /Gm;
            /Od;
            /RTC1;
            /MTd;
            /ZI
        >
        $<$<CONFIG:Release>:
            /MT;
            /Zi
        >
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:anypiabDebug>:
            /INCREMENTAL
        >
        $<$<CONFIG:anypiabRelease>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:anypiacDebug>:
            /INCREMENTAL
        >
        $<$<CONFIG:anypiacRelease>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:Debug>:
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /DEBUG;
        /MACHINE:X86;
        /SUBSYSTEM:CONSOLE;
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    misc
    piadata
    piaout
    windows
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    misc
    piadata
    piaout
    windows
)
############
# https://stackoverflow.com/questions/15724357/using-boost-with-emscripten
############
set_target_properties (${PROJECT_NAME} PROPERTIES 
COMPILE_FLAGS "-s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0"
LINK_FLAGS "--bind --emrun -s TOTAL_MEMORY=500MB -s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0"
)
# target_link_directories(${PROJECT_NAME} PUBLIC
#     "${CMAKE_CURRENT_SOURCE_DIR}/../oactobjs32/boost_1_64_0/stage/lib"
# )


