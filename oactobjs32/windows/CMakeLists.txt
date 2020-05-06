project(windows C CXX)

################################################################################
# Source groups
################################################################################
set(Headers
    "BitAnnualBase.h"
    "BitAnnualInlines.h"
    "chdir.h"
    "CommaBase.h"
    "Floor.h"
    "getopt.h"
    "gnumath.h"
    "isspace.h"
    "math_private.h"
    "OutDC.h"
    "OutFile132.h"
    "OutFile80.h"
    "PathnameSeparator.h"
    "PragmaWarningDisable4786.h"
    "strcasecmp.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "BitAnnualBase.cpp"
    "erf.c"
    "getopt.c"
    "getopt_long.c"
    "libyywrap.c"
    "OutDC.cpp"
    "OutFile132.cpp"
    "OutFile80.cpp"
    "strcasecmp.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_ANYPIABDEBUG   "windows"
    TARGET_NAME_ANYPIABRELEASE "windows"
    TARGET_NAME_ANYPIACDEBUG   "windows"
    TARGET_NAME_ANYPIACRELEASE "windows"
    TARGET_NAME_DEBUG          "windows"
    TARGET_NAME_RELEASE        "windows"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_ANYPIABDEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_ANYPIABRELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release"
    OUTPUT_DIRECTORY_ANYPIACDEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_ANYPIACRELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release"
    OUTPUT_DIRECTORY_DEBUG          "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_RELEASE        "${CMAKE_CURRENT_SOURCE_DIR}/Release"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/..;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../boost_1_64_0"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:anypiabDebug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:anypiabRelease>:"
        "NDEBUG"
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
        "NDEBUG"
    ">"
    "WIN32;"
    "_LIB;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:anypiabDebug>:
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
        /wd4267;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
endif()

