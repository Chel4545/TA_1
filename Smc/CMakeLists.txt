add_library(smc_module STATIC
        lexer.cpp
        lexer.h
        SmcClass.cpp
        SmcClass.h
)

target_include_directories(regex_module PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(regex_module PUBLIC store)