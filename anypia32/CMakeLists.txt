cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project(anypia32 CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_CXX_FLAGS "")
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


project(anypia32 CXX)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/res/Anypia32.ico"
    "${CMAKE_CURRENT_SOURCE_DIR}/res/Anypia32Doc.ico"
    "${CMAKE_CURRENT_SOURCE_DIR}/res/Toolbar.bmp"
    "${CMAKE_CURRENT_SOURCE_DIR}/resource.hm"
)
source_group("" FILES ${no_group_source_files})

set(Headers
    "Anypia32.h"
    "anypiadoc.h"
    "AnypiaView.h"
    "AssumptionsDialog.h"
    "AwbidatIni.h"
    "AwincIni.h"
    "AwprojDialog.h"
    "AwsetDialog.h"
    "BaseyearDialog.h"
    "BaseyearIni.h"
    "BiprojDialog.h"
    "BiprojIni.h"
    "BisetDialog.h"
    "CachupIni.h"
    "ConfigDialog.h"
    "ConfigIni.h"
    "CuprojDialog.h"
    "CusetDialog.h"
    "DeathDialog.h"
    "DisabDialog.h"
    "EarningsDialog.h"
    "FoinfoDialog.h"
    "FoinfoIni.h"
    "HistAmtClearDialog.h"
    "HistAmtModifyDialog.h"
    "HistAmtReviewDialog.h"
    "HistAmtUpdateDialog.h"
    "Introduction.h"
    "MainFrm.h"
    "Milserv.h"
    "NonPebesDialog.h"
    "../oactobjs32/windows/outdc.h"
    "PebesDialog.h"
    "pia.h"
    "QctotDialog.h"
    "resource.h"
    "ScreenDialog.h"
    "StdAfx.h"
    "TextFloatFormatPatch.h"
    "WageBaseDialog.h"
    "WorkerDialog.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "Anypia32.cpp"
    "anypiadoc.cpp"
    "AnypiaView.cpp"
    "AssumptionsDialog.cpp"
    "AwbidatIni.cpp"
    "AwincIni.cpp"
    "AwprojDialog.cpp"
    "AwsetDialog.cpp"
    "BaseyearDialog.cpp"
    "BaseyearIni.cpp"
    "BiprojDialog.cpp"
    "BiprojIni.cpp"
    "BisetDialog.cpp"
    "CachupIni.cpp"
    "ConfigDialog.cpp"
    "ConfigIni.cpp"
    "CuprojDialog.cpp"
    "CusetDialog.cpp"
    "DeathDialog.cpp"
    "DisabDialog.cpp"
    "EarningsDialog.cpp"
    "FoinfoDialog.cpp"
    "FoinfoIni.cpp"
    "FormatString.cpp"
    "HistAmtClearDialog.cpp"
    "HistAmtModifyDialog.cpp"
    "HistAmtReviewDialog.cpp"
    "HistAmtUpdateDialog.cpp"
    "Introduction.cpp"
    "MainFrm.cpp"
    "Milserv.cpp"
    "NonPebesDialog.cpp"
    "PebesDialog.cpp"
    "QctotDialog.cpp"
    "ScreenDialog.cpp"
    "StdAfx.cpp"
    "TextFloatFormatPatch.cpp"
    "WageBaseDialog.cpp"
    "WorkerDialog.cpp"
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
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "anypia32"
    TARGET_NAME_RELEASE "anypia32"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
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
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "WIN32;"
    "_WINDOWS;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /RTC1;
            /MTd;
            /ZI
        >
        $<$<CONFIG:Release>:
            /MT;
            /Zi
        >
        /Gm;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
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
        /SUBSYSTEM:WINDOWS;
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

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../oactobjs32/boost_1_64_0/stage/lib"
)

################################################################################
# Sub-projects
################################################################################
add_subdirectory(../oactobjs32/misc ${CMAKE_BINARY_DIR}/misc)
add_subdirectory(../oactobjs32/piadata ${CMAKE_BINARY_DIR}/piadata)
add_subdirectory(../oactobjs32/piaout ${CMAKE_BINARY_DIR}/piaout)
add_subdirectory(../oactobjs32/windows ${CMAKE_BINARY_DIR}/windows)