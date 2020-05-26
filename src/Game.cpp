#include <iostream>
#include "./Constants.h"
#include "./Game.h"

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
float projectTilePosX = 0.0f;
float projectTilePosY = 0.0f;
float projectTileVelX = 20.0f;
float projectTileVelY = 10.0f;

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
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    float deltaTime = (SDL_GetTicks() - ticksLastFrame)/1000.0f;
    deltaTime = (deltaTime > 0.05) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();
    
    projectTilePosX += projectTileVelX * deltaTime;
    projectTilePosY += projectTileVelY * deltaTime;
    
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    SDL_RenderClear(renderer);
    SDL_Rect projectTile{
        (int)projectTilePosX,
        (int)projectTilePosY,
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