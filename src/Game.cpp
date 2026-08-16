#include "Game.hpp"

#include <iostream>
#include <format>
#include <cstdint>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>

Game::Game(){
    const auto text = std::format("Hey hey");
    std::cout << text << "\n";
    m_is_running = false;
}

Game::~Game(){}

void Game::Initialize(){
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD)){
        std::cerr << "Error initializing SDL! " << SDL_GetError() << "\n";
        return;
    }

    const auto window_title = "My Game Window";
 
    // Região de código para pegar os dados da janela pegando do Display/Monitor que está sendo usado.
    const auto current_display = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode *display_mode = SDL_GetCurrentDisplayMode(current_display);
    if(!display_mode){
        std::cerr << "Error Getting display mode! " << SDL_GetError() << "\n";
        return;
    }
    // m_window_width = display_mode->w;
    // m_window_height = display_mode->h;
    // fake fullscreen
    m_window_width = 800;
    m_window_height = 600;
    m_window = SDL_CreateWindow(window_title, m_window_width, m_window_height, SDL_WINDOW_BORDERLESS);
    if(!m_window){
        std::cerr << "Error initialing Window! " << SDL_GetError() << "\n";
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if(!m_renderer){
        std::cerr << "Error initializing Renderer! " << SDL_GetError() << "\n";
        return;
    }

    // seta o video mode para full screen
    // SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

    m_is_running = true;
}

void Game::Run(){
    Setup();
    
    std::uint32_t fps_counter = 0;
    std::uint64_t now;
    std::uint64_t fps_anchor = SDL_GetTicksNS();
    std::uint64_t next_deadline = SDL_GetTicksNS() + NANO_SECONDS_PER_FRAME;

    while(m_is_running){
        ProcessInput();
        Update();
        Render();
        
        now = SDL_GetTicksNS();
        
        fps_counter++;
        if(now - fps_anchor >= ONE_SECOND_IN_NANO){
            fps_anchor+=ONE_SECOND_IN_NANO;
            std::cout << "[FPS] - " << fps_counter << "\n";
            fps_counter = 0;
        }

        if(now < next_deadline){
            SDL_DelayPrecise(next_deadline - now);
        }

        next_deadline += NANO_SECONDS_PER_FRAME;
    }
}

void Game::ProcessInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_EVENT_QUIT: {
                m_is_running = false;
                break;
            }

            case SDL_EVENT_KEY_DOWN:{
                if(event.key.key == SDLK_ESCAPE){
                    m_is_running = false;
                }
                break;
            }
        }
    }
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup(){
    playerPosition = glm::vec2(10.0, 20.0);
    playerVelocity = glm::vec2(0.4, 0.0);
}


void Game::Update(){
   playerPosition.x += playerVelocity.x;
   playerPosition.y += playerVelocity.y;
}

void Game::Render(){
    SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_renderer);
    
    // // Todo Render all game object`s
    // SDL_FRect player = {.x=10, .y=10, .w=20, .h=20};
    // SDL_SetRenderDrawColor(m_renderer, 255, 255,255,255);
    // SDL_RenderFillRect(m_renderer, &player);

    // Loads a PNG texture
    SDL_Surface *surface = IMG_Load("./assets/images/tank-big-right.png");
    if(!surface){
        std::cerr << "Error loading surface: " << SDL_GetError() <<"\n";
        return; 
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if(!texture){
        std::cerr << "Error loading texture: " << SDL_GetError() << "\n";
        return;
    }
    SDL_DestroySurface(surface);

    SDL_FRect dest = {.x=playerPosition.x, .y=playerPosition.y, .w=32.0, .h=32.0};
    SDL_RenderTexture(m_renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    

    SDL_RenderPresent(m_renderer);
}

void Game::Destroy(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

