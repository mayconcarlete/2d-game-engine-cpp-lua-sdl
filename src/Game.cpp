#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"

Game::Game(){
    this->isRunning = false;
    std::cout<<"Valor de renderer1: " <<this->renderer<<"\n";
    std::cout<<"Valor do ponteiro: " <<&renderer<<"\n";
}

Game::~Game(){
    
}
bool Game::IsRunning() const{
    return this->isRunning;
}

glm::vec2 projectTilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectTileVel = glm::vec2(20.0f, 20.0f);

void Game::Initialize(int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr<<"Error initializing SDL." <<"\n";
        return;
    }
    window = SDL_CreateWindow("Hello World", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED,
    width,
    height,
    SDL_WINDOW_BORDERLESS
    );
    if(!window){
        std::cerr<<"Window Error create window"<<"\n";
        return;
    }

    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer){
        std::cerr <<"Redeerer error"<<"\n";
        return;
    }
  isRunning = true;
  return;  
}

void Game::ProcessInput(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:{
        isRunning = false;
        break;
    }
    
    case SDL_KEYDOWN:{
        if(event.key.keysym.sym == SDLK_ESCAPE){
            isRunning = false;
        }
    }
    default:
        break;
    }
}

void Game::Update(){
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks()-ticksLastFrame);
    if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }
    float deltaTime = (SDL_GetTicks() - ticksLastFrame)/1000.0f;
    deltaTime = (deltaTime > 0.05) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();   
    projectTilePos= glm::vec2(
        projectTilePos.x += projectTileVel.x * deltaTime,
        projectTilePos.y += projectTileVel.y * deltaTime
    );
    
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    SDL_RenderClear(renderer);
    SDL_Rect projectTile{
        (int)projectTilePos.x,
        (int)projectTilePos.y,
        10,
        10
    };
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &projectTile);
    SDL_RenderPresent(renderer);
}
void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}