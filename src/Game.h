#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./EntityManager/EntityManager.h"
#include "./Entity/Entity.h"
#include "./Component/Component.h"

class AssetManager;

class Game{
    private:
        bool isRunning;
        SDL_Window *window;
    public:
        Game();
        ~Game();
        bool IsRunning() const;
        static SDL_Renderer *renderer;
        static AssetManager* assetManager;
        void LoadLevel(int levelNumber);
        Uint32 ticksLastFrame = 0;
        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
};

#endif