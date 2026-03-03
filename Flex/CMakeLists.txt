add_library(flex_module STATIC
        #example.cpp
)

target_include_directories(flex_module PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(flex_module PUBLIC store)