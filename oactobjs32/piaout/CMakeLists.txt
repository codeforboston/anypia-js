project(piaout CXX)


################################################################################
# Source groups
################################################################################

set(Headers
    "AnypiaOut.h"
    "ChildCareCalc1Page.h"
    "ChildCareCalc2Page.h"
    "DibGuarPage.h"
    "EarningsPage.h"
    "FamilyPage.h"
    "FrozMinPage.h"
    "InsuredPage.h"
    "OldStart1Page.h"
    "OldStart2Page.h"
    "OnePage.h"
    "PebsCreditInfo.h"
    "PebsEarnings.h"
    "PebsEarningsInfo.h"
    "PebsLetter.h"
    "PebsOasdiEst.h"
    "PebsOasdiInfo.h"
    "PebsOut.h"
    "PebsPageOut.h"
    "PebsWorkerEarnings.h"
    "PebsWorkerInfo.h"
    "PiaOut.h"
    "PiaPageOut.h"
    "PiaTable1Page.h"
    "PiaTable2Page.h"
    "ReindWid1Page.h"
    "ReindWid2Page.h"
    "../include/resource.h"
    "SpecMin1Page.h"
    "SpecMin2Page.h"
    "Summary1Page.h"
    "Summary2Page.h"
    "Summary3Page.h"
    "SummaryPage.h"
    "TaxesPage.h"
    "TransGuar1Page.h"
    "TransGuar2Page.h"
    "WageInd1Page.h"
    "WageInd2Page.h"
    "WageIndNonFreeze1Page.h"
    "WageIndNonFreeze2Page.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "AnypiaOut.cpp"
    "ChildCareCalc1Page.cpp"
    "ChildCareCalc2Page.cpp"
    "DibGuarPage.cpp"
    "EarningsPage.cpp"
    "FamilyPage.cpp"
    "FrozMinPage.cpp"
    "InsuredPage.cpp"
    "OldStart1Page.cpp"
    "OldStart2Page.cpp"
    "OnePage.cpp"
    "PebsCreditInfo.cpp"
    "PebsEarnings.cpp"
    "PebsEarningsInfo.cpp"
    "PebsLetter.cpp"
    "PebsOasdiEst.cpp"
    "PebsOasdiInfo.cpp"
    "PebsOut.cpp"
    "PebsPageOut.cpp"
    "PebsWorkerEarnings.cpp"
    "PebsWorkerInfo.cpp"
    "PiaOut.cpp"
    "PiaPageOut.cpp"
    "PiaTable1Page.cpp"
    "PiaTable2Page.cpp"
    "ReindWid1Page.cpp"
    "ReindWid2Page.cpp"
    "SpecMin1Page.cpp"
    "SpecMin2Page.cpp"
    "Summary1Page.cpp"
    "Summary2Page.cpp"
    "Summary3Page.cpp"
    "SummaryPage.cpp"
    "TaxesPage.cpp"
    "TransGuar1Page.cpp"
    "TransGuar2Page.cpp"
    "WageInd1Page.cpp"
    "WageInd2Page.cpp"
    "WageIndNonFreeze1Page.cpp"
    "WageIndNonFreeze2Page.cpp"
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

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_ANYPIABDEBUG   "piaout"
    TARGET_NAME_ANYPIABRELEASE "piaout"
    TARGET_NAME_ANYPIACDEBUG   "piaout"
    TARGET_NAME_ANYPIACRELEASE "piaout"
    TARGET_NAME_DEBUG          "piaout"
    TARGET_NAME_RELEASE        "piaout"
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
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
endif()

############
# https://stackoverflow.com/questions/15724357/using-boost-with-emscripten
############
#set_target_properties( ${PROJECT_NAME} PROPERTIES 
#    COMPILE_FLAGS "-s USE_BOOST_HEADERS=1" LINK_FLAGS "-s USE_BOOST_HEADERS=1"
#    )