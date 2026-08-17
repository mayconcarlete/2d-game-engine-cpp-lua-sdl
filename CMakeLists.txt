cmake_minimum_required(VERSION 3.21)

project(game-engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(sol2 CONFIG REQUIRED)

add_subdirectory(src/Logger)
add_subdirectory(src/Game)

add_executable(game-engine
    src/main.cpp
)

target_link_libraries(game-engine PRIVATE
    Game
    Logger
    sol2::sol2
    ${LUA_LIBRARIES}
)

target_include_directories(game-engine PRIVATE ${LUA_INCLUDE_DIR})

# Deixa a pasta assets acessível ao lado do executável.
add_custom_command(TARGET game-engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:game-engine>/assets
)
