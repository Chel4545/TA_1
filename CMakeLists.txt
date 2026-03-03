cmake_minimum_required(VERSION 3.31)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Store)
add_subdirectory(RegEx)
add_subdirectory(Flex)

add_executable(lab1 main.cpp)

target_link_libraries(lab1 PRIVATE store regex_module)

target_include_directories(lab1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/RegEx
        ${CMAKE_CURRENT_SOURCE_DIR}/Store
        ${CMAKE_CURRENT_SOURCE_DIR}/Flex
)