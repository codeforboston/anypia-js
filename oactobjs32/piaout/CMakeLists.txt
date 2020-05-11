cmake_minimum_required(VERSION 3.10)

project(piaout)

set(SOURCES
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

find_package(Boost 1.64.0 REQUIRED COMPONENTS date_time)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/../include"
    "${PROJECT_SOURCE_DIR}/../windows"
    ${Boost_INCLUDE_DIRS}
)
