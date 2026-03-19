add_executable(timing_app
        timing.cpp
)

target_compile_definitions(timing_app PRIVATE
        TIMING_CASES_DIR="${CMAKE_SOURCE_DIR}/Timing/timing_cases"
)

target_link_libraries(timing_app PRIVATE
        store
        regex_module
        smc_module
        flex_module
)

target_include_directories(timing_app PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Store
        ${CMAKE_SOURCE_DIR}/RegEx
        ${CMAKE_SOURCE_DIR}/Smc
        ${CMAKE_SOURCE_DIR}/Flex
)