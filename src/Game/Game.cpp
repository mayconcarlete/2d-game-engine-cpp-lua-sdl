#include <Game/Game.hpp>

#include <iostream>
#include <format>
#include <cstdint>
#include <Logger/Logger.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>

Game::Game()
{
    m_is_running = false;
}

Game::~Game() {}

void Game::Initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD))
    {
        const auto text = std::format("Error initializing SDL! - {}", SDL_GetError());
        Logger::Error(text);
        return;
    }

    const auto window_title = "My Game Window";
    // Região de código para pegar os dados da janela pegando do Display/Monitor que está sendo usado.
    const auto current_display = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode *display_mode = SDL_GetCurrentDisplayMode(current_display);
    if (!display_mode)
    {
        const auto text = std::format("Error Getting display mode! - {}", SDL_GetError());
        Logger::Error(text);
        return;
    }
    // m_window_width = display_mode->w;
    // m_window_height = display_mode->h;
    // fake fullscreen
    m_window_width = 800;
    m_window_height = 600;
    m_window = SDL_CreateWindow(window_title, m_window_width, m_window_height, SDL_WINDOW_BORDERLESS);
    if (!m_window)
    {
        const auto text = std::format("Error initialing Window! - {}", SDL_GetError());
        Logger::Error(text);
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer)
    {
        const auto text = std::format("Error initializing Renderer! - {}", SDL_GetError());
        Logger::Error(text);
        return;
    }

    // seta o video mode para full screen
    // SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

    m_is_running = true;
}

void Game::Run()
{
    Setup();

    std::uint32_t fps_counter = 0;
    std::uint64_t current_tick = SDL_GetTicksNS();
    std::uint64_t now = current_tick;
    std::uint64_t fps_anchor = current_tick;
    std::uint64_t next_deadline = current_tick + NANO_SECONDS_PER_FRAME;
    std::uint64_t previous_frame_ns = current_tick;
    float max_delta_time = 0.05f;

    while (m_is_running)
    {
        ProcessInput();
        m_delta_time = static_cast<float>(now - previous_frame_ns) / 1000000000.0f;
        if (m_delta_time > max_delta_time)
            m_delta_time = max_delta_time;
        Update();
        Render();

        previous_frame_ns = now;
        now = SDL_GetTicksNS();

        fps_counter++;
        if (now - fps_anchor >= ONE_SECOND_IN_NANO)
        {
            fps_anchor += ONE_SECOND_IN_NANO;
            const auto text = std::format("[FPS] - {}", fps_counter);
            Logger::Info(text);
            fps_counter = 0;
        }

        if (now < next_deadline)
        {
            SDL_DelayPrecise(next_deadline - now);
        }

        next_deadline += NANO_SECONDS_PER_FRAME;
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
        {
            m_is_running = false;
            break;
        }

        case SDL_EVENT_KEY_DOWN:
        {
            if (event.key.key == SDLK_ESCAPE)
            {
                m_is_running = false;
            }
            break;
        }
        }
    }
}

void Game::Setup()
{
    // Todo
    // Entity tank = registry.CreateEntity();
    // tank.AddComponent<TransformComponent>();
    // tank.AddComponent<BoxColliderComponent>()
    // tank.AddComponent<SpriteComponent>();
}

void Game::Update()
{
    // MovementeSystem.Update(m_delta_time);
    // Collision system
    // DamageSystem
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_renderer);

    // REnder Game Objects

    SDL_RenderPresent(m_renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
