add_library(Game STATIC
    Game.cpp
)

target_include_directories(Game PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Game
    # SDL3 é PUBLIC porque Game.hpp expõe SDL_Window/SDL_Renderer.
    PUBLIC SDL3::SDL3
    PRIVATE
        Logger
        SDL3_image::SDL3_image
        glm::glm
)
