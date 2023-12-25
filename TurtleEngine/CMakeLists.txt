set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(HEADERS
    ${INCLUDE_DIR}/App.h
    ${INCLUDE_DIR}/Scene.h
    ${INCLUDE_DIR}/SceneManager.h
    ${INCLUDE_DIR}/AudioManager.h
    ${INCLUDE_DIR}/Utils/Clock.h
    ${INCLUDE_DIR}/Utils/Singleton.h
    ${INCLUDE_DIR}/Utils/Time.h
)

set(SOURCES
    ${SRC_DIR}/App.cpp
    ${SRC_DIR}/SceneManager.cpp
    ${SRC_DIR}/AudioManager.cpp
    ${SRC_DIR}/Utils/Time.cpp
)

add_library(TurtleEngine
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(TurtleEngine
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${INCLUDE_DIR}>
    PRIVATE
        ${SRC_DIR}
)

target_link_libraries(TurtleEngine 
    PUBLIC
        sfml-system sfml-graphics sfml-window sfml-audio
        imgui::imgui
        ImGui-SFML::ImGui-SFML
)