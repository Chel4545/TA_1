cmake_minimum_required(VERSION 3.31)

find_package(FLEX REQUIRED)

FLEX_TARGET(FlexScanner
        ${CMAKE_CURRENT_SOURCE_DIR}/flex.l
        ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
)

set_source_files_properties(${FLEX_FlexScanner_OUTPUTS} PROPERTIES LANGUAGE CXX)

add_library(flex_module STATIC
        ${FLEX_FlexScanner_OUTPUTS}
)

target_include_directories(flex_module PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(flex_module PUBLIC store)