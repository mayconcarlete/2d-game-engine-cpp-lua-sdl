#pragma once

#include <cstdint>
#include <SDL3/SDL.h>

const std::uint64_t ONE_SECOND_IN_NANO = 1000000000;
const std::uint64_t FPS = 100;
const std::uint64_t NANO_SECONDS_PER_FRAME = ONE_SECOND_IN_NANO/FPS;

class Game {
    private:
        bool m_is_running;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        std::uint64_t m_start_frame_nano_seconds = 0;
    public:
        Game();
        ~Game();
        void Initialize();
        void Run();
        void Setup();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        int m_window_width;
        int m_window_height;
};