set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE HEADERS
    "${INCLUDE_DIR}/*.h"
    "${INCLUDE_DIR}/*.hxx"
)

file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.cpp"
)

add_executable(TurtleEditor
    ${HEADERS}
    ${SOURCES}
)

# Headers
foreach(_header IN ITEMS ${HEADERS})
    get_filename_component(_header_path "${_header}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}/TurtleEditor" "" _header_path "${_header_path}")
    string(REPLACE "/" "\\" _header_path "${_header_path}")
    source_group("${_header_path}" FILES "${_header}")
endforeach()

# Sources
foreach(_source IN ITEMS ${SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}/TurtleEditor" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

target_link_libraries(TurtleEditor TurtleEngine)