#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager/AssetManager.h"
#include "./Components-parts/TransformComponent.h"
#include "./Components-parts/SpriteComponent.h"
#include "./Components-parts/Animation.h"
#include "../lib/glm/glm.hpp"

//ListAllEntities()
//ListAllComponents()

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

Game::Game(){
    this->isRunning = false;
}

Game::~Game(){
    
}
bool Game::IsRunning() const{
    return this->isRunning;
}

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
    LoadLevel(0);
    isRunning = true;
  return;  
}
void Game::LoadLevel(int levelNumber){
    
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    
    Entity& tankEntity(manager.AddEntity("tank"));
    tankEntity.AddComponent<TransformComponent>(0,0,20,20,32,32,1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");

    Entity& chopperEntity(manager.AddEntity("chopper"));
    chopperEntity.AddComponent<TransformComponent>(240,106,0,0,32,32,1);
    chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);

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
            std::cout<<"CLicou no ESC"<<"\n";
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
    manager.Update(deltaTime);
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    SDL_RenderClear(renderer);

    if(manager.HasNoEntities()){
        return;
    }
    manager.Render();

    SDL_RenderPresent(renderer);
}
void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}