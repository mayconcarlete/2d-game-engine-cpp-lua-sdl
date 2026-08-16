#pragma once

#include <cstdint>
#include <SDL3/SDL.h>
const int FPNS = 100;
const int MILLISECONDS_PER_FRAME = 1000000000/FPNS;

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