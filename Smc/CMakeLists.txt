set(SMC_JAR ${CMAKE_CURRENT_SOURCE_DIR}/tools/smc/Smc.jar)
set(SMC_RUNTIME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools/smc)

set(SMC_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/SmcLogic.sm)
set(SMC_GENERATED_CPP ${CMAKE_CURRENT_SOURCE_DIR}/ContextFSM.cpp)
set(SMC_GENERATED_H ${CMAKE_CURRENT_SOURCE_DIR}/ContextFSM.h)

find_package(Java REQUIRED)

add_custom_command(
        OUTPUT ${SMC_GENERATED_CPP} ${SMC_GENERATED_H}
        COMMAND ${Java_JAVA_EXECUTABLE} -jar ${SMC_JAR} -c++ -d ${CMAKE_CURRENT_SOURCE_DIR} ${SMC_SOURCE}
        DEPENDS ${SMC_SOURCE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating SMC state machine from SmcLogic.sm"
        VERBATIM
)

add_library(smc_module STATIC
        ${SMC_GENERATED_CPP}
        ContextFSM.h
        ContextFSM.cpp
        SmcClass.h
        SmcClass.cpp
        Tokenizer.h
        Tokenizer.cpp
        Tokens.h
        SmcParser.h
        SmcParser.cpp
)

target_include_directories(smc_module PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/smc
        ${SMC_RUNTIME_DIR}
)

target_link_libraries(smc_module PUBLIC store)