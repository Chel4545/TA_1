add_library(regex_module STATIC
        RegEx.h
        RegEx.cpp
)

target_include_directories(regex_module PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(regex_module PUBLIC store)