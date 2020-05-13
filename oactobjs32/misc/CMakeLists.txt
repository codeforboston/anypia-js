project(misc CXX)
cmake_minimum_required(VERSION 3.17)


if(CMAKE_CXX_COMPILER MATCHES "/em(-[a-zA-Z0-9.])?(\.bat)?")
  message(" * C++ compiler: Emscripten")
  set(CMAKE_CXX_COMPILER_ID "Emscripten")
else()
  message(" * C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()
################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../../anypia32/res/Toolbar.bmp"
)
source_group("" FILES ${no_group_source_files})

set(Headers
    "../include/age.h"
    "../include/AnnualArrays.h"
    "../include/BitAnnual.h"
    "../include/cminmax.h"
    "../include/comma.h"
    "../include/date.h"
    "../include/DateFormatter.h"
    "../include/datemodyyr.h"
    "../include/datemoyr.h"
    "../include/dbleann.h"
    "../include/dblemth.h"
    "../include/dbleqtr.h"
    "../include/document.h"
    "../include/DoubleAnnualRW.h"
    "../include/floatann.h"
    "../include/floatmth.h"
    "../include/floatqtr.h"
    "../include/FormatString.h"
    "../include/genfile.h"
    "../include/intann.h"
    "../include/NumPunct.h"
    "../include/outfile.h"
    "../include/OutfileHTML.h"
    "../include/page.h"
    "../include/PageOut.h"
    "../include/Path.h"
    "../include/pathname.h"
    "../include/PiaException.h"
    "../include/qtryear.h"
    "../include/Sex.h"
    "../include/ssn.h"
    "../include/StringParser.h"
    "../include/TextWriterTraceListener.h"
    "../include/Trace.h"
    "../include/TraceListener.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "age.cpp"
    "AnnualArrays.cpp"
    "BitAnnual.cpp"
    "comma.cpp"
    "date.cpp"
    "DateFormatter.cpp"
    "datemoyr.cpp"
    "dbleann.cpp"
    "dblemth.cpp"
    "dbleqtr.cpp"
    "document.cpp"
    "DoubleAnnualRW.cpp"
    "floatann.cpp"
    "floatmth.cpp"
    "floatqtr.cpp"
    "genfile.cpp"
    "intann.cpp"
    "NumPunct.cpp"
    "outfile.cpp"
    "OutfileHTML.cpp"
    "page.cpp"
    "PageOut.cpp"
    "Path.cpp"
    "PiaException.cpp"
    "qtryear.cpp"
    "Sex.cpp"
    "ssn.cpp"
    "StringParser.cpp"
    "TextWriterTraceListener.cpp"
    "Trace.cpp"
    "TraceListener.cpp"
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
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

#use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_ANYPIABDEBUG   "misc"
    TARGET_NAME_ANYPIACDEBUG   "misc"
    TARGET_NAME_DEBUG          "misc"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_ANYPIABDEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_ANYPIABRELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release/"
    OUTPUT_DIRECTORY_ANYPIACDEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_ANYPIACRELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release/"
    OUTPUT_DIRECTORY_DEBUG          "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_RELEASE        "${CMAKE_CURRENT_SOURCE_DIR}/Release/"
)


################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/..;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../windows;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../boost_1_64_0"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Emscripten")
    set(CMAKE_CXX_FLAGS "-fdeclspec")
    
    ############
    # https://stackoverflow.com/questions/15724357/using-boost-with-emscripten
    ############
    # set_target_properties (${PROJECT_NAME} PROPERTIES 
    # COMPILE_FLAGS "-s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0"
    # LINK_FLAGS "--bind --emrun -s TOTAL_MEMORY=500MB -s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0"
    # )

else()
    set(CMAKE_CXX_FLAGS "/EHsc")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../boost_1_64_0"
    )
endif()


################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:anypiabDebug>:"
        "_DEBUG;"
        "_LIB"
    ">"
    "$<$<CONFIG:anypiabRelease>:"
        "NDEBUG;"
        "_WINDOWS"
    ">"
    "$<$<CONFIG:anypiacDebug>:"
        "_DEBUG;"
        "_LIB"
    ">"
    "$<$<CONFIG:anypiacRelease>:"
        "NDEBUG;"
        "_WINDOWS"
    ">"
    "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "_LIB"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "_WINDOWS"
    ">"
    "WIN32;"
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
            /W3;
            /ZI;
            /Y-
        >
        $<$<CONFIG:anypiabRelease>:
            /MT;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:anypiacDebug>:
            /Od;
            /RTC1;
            /MTd;
            /W3;
            /ZI;
            /Y-
        >
        $<$<CONFIG:anypiacRelease>:
            /MT;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:Debug>:
            /Od;
            /RTC1;
            /MTd;
            /W3;
            /ZI;
            /Y-
        >
        $<$<CONFIG:Release>:
            /MT;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /Gm;
        /wd4251;
        /wd4275;
        /wd4267;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    string(CONCAT FILE_CL_OPTIONS
        "$<$<CONFIG:anypiabDebug>:"
            "/Y-"
        ">"
        "$<$<CONFIG:anypiacDebug>:"
            "/Y-"
        ">"
        "$<$<CONFIG:Debug>:"
            "/Y-"
        ">"
    )
    source_file_compile_options(TraceListener.cpp ${FILE_CL_OPTIONS})
endif()
