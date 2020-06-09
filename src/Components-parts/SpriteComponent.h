#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager/TextureManager.h"
#include "../AssetManager/AssetManager.h"
#include "./TransformComponent.h"
#include "./Animation.h"

class SpriteComponent: public Component{
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRect;
        SDL_Rect destRect;
        bool isAnimated;
        int numFrames;
        int animationSpeed;
        bool isFixed;
        std::map<std::string, Animation> animations;
        std::string currentAnimationName;
        unsigned int animationIndex =  0;
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
        SpriteComponent(const char * filePath){
            SetTexture(filePath);
        }
    
        void SetTexture(std::string assetTextureId){
            texture = Game::assetManager ->GetTexture(assetTextureId);
        }
        SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed){
            this->isAnimated = true;
            this->numFrames = numFrames;
            this->animationSpeed = animationSpeed;
            this->isFixed = isFixed;

            if(hasDirections){
                Animation downAnimation = Animation(0, numFrames, animationSpeed);
                Animation rightAnimation = Animation(1, numFrames, animationSpeed);
                Animation leftAnimation = Animation(2, numFrames, animationSpeed);
                Animation upAnimation = Animation(3, numFrames, animationSpeed);

                animations.emplace("DownAnimation", downAnimation);
                animations.emplace("RightAnimation", rightAnimation);
                animations.emplace("LeftAnimation", leftAnimation);
                animations.emplace("UpAnimation", upAnimation);

                this->animationIndex = 0;
                this->currentAnimationName = "DownAnimation";
            } else{
                Animation singleAnimation = Animation(0, numFrames, animationSpeed);
                animations.emplace("SingleAnimation", singleAnimation);
                this->animationIndex = 0;
                this->currentAnimationName = "SingleAnimation";
            }
            Play(this->currentAnimationName);
            SetTexture(id);
        }
        void Play(std::string animationName){
            numFrames = animations[animationName].numFrames;
            animationIndex = animations[animationName].index;
            animationSpeed = animations[animationName].animationSpeed;
            currentAnimationName = animationName;
        }
        void Initialize() override{
            transform = owner->GetComponent<TransformComponent>();
            sourceRect.x = 0;
            sourceRect.y = 0;
            sourceRect.w = transform->width;
            sourceRect.h = transform->height;
        }
        void Update(float deltaTime) override{
            
            if(isAnimated){
                sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks()/animationSpeed)%numFrames);
            }
            sourceRect.y = animationIndex * transform->height;
            
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
        }
        void Render() override{
            TextureManager::Draw(texture, sourceRect, destRect, spriteFlip);
        }
};

#endif