cmake_minimum_required(VERSION 3.16)
project(ReactionLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(REACTION_LAB_SOURCES
    src/main.cpp
    src/Game.cpp
    src/Storage.cpp
    src/Utils.cpp
)

add_executable(reaction_lab ${REACTION_LAB_SOURCES})

target_include_directories(reaction_lab PRIVATE include)

if(APPLE)
    add_custom_command(TARGET reaction_lab POST_BUILD
        COMMAND /bin/bash "${CMAKE_SOURCE_DIR}/scripts/apply_macos_icon.sh"
                "$<TARGET_FILE:reaction_lab>"
                "${CMAKE_SOURCE_DIR}/resources/reaction_lab_cover.png"
        COMMENT "Applying custom macOS Finder icon to reaction_lab"
        VERBATIM
    )
endif()
