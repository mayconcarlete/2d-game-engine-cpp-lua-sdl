#pragma once

#include <SDL3/SDL.h>

class Game {
    private:
        bool m_is_running;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

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