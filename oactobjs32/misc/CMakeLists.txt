cmake_minimum_required(VERSION 3.10)

project(misc)

set(SOURCES
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

find_package(Boost 1.64.0 REQUIRED COMPONENTS date_time)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/../include"
    "${PROJECT_SOURCE_DIR}/../windows"
    ${Boost_INCLUDE_DIRS}
)
