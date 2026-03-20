cmake_minimum_required(VERSION 3.31)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PARSER "regex" CACHE STRING "Parser implementation: regex|flex|smc")
set_property(CACHE PARSER PROPERTY STRINGS regex flex smc)

add_subdirectory(Store)
add_subdirectory(RegEx)
add_subdirectory(Smc)
add_subdirectory(Flex)
add_subdirectory(Timing)

add_executable(lab1 main.cpp)

target_link_libraries(lab1 PRIVATE store)

if(PARSER STREQUAL "regex")
    target_link_libraries(lab1 PRIVATE regex_module)
    target_compile_definitions(lab1 PRIVATE PARSER_REGEX)
elseif(PARSER STREQUAL "smc")
    target_link_libraries(lab1 PRIVATE smc_module)
    target_compile_definitions(lab1 PRIVATE PARSER_SMC)
elseif(PARSER STREQUAL "flex")
    target_link_libraries(lab1 PRIVATE flex_module)
    target_compile_definitions(lab1 PRIVATE PARSER_FLEX)
else()
    message(FATAL_ERROR "Unknown PARSER='${PARSER}'. Use regex|flex|smc.")
endif()

target_include_directories(lab1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Store
        ${CMAKE_CURRENT_SOURCE_DIR}/RegEx
        ${CMAKE_CURRENT_SOURCE_DIR}/Smc
        ${CMAKE_CURRENT_SOURCE_DIR}/Flex
)