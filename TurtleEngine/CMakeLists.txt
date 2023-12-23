project(TurtleEngine)

set (INPUT_SYSTEM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/InputSystem)

set (HEADERS
    ${INPUT_SYSTEM_DIR}/UIEvents.h
)

set (SOURCES
    ${INPUT_SYSTEM_DIR}/UIEvents.cpp
)

add_library(${PROJECT_NAME}
    STATIC
        ${HEADERS}
        ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${HEADER_DIR}>
)