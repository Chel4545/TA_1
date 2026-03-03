add_library(store STATIC
        RelationStore.h
        RelationStore.cpp
)

target_include_directories(store PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)