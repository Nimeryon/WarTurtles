set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(WarTurtles ${SRC_DIR}/main.cpp)

target_link_libraries(WarTurtles TurtleEngine)