#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager/EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include "../Game.h"

class TransformComponent: public Component{
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;
        TransformComponent(int posX, int posY, int velX, int velY, int width, int height, int scale){
            position = glm::vec2(posX, posY);
            velocity = glm::vec2(velX, velY);
            this->width = width;
            this->height = height;
            this->scale = scale;
        }
        void Initialize() override{

        }

        void Update(float deltaTime) override {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
            
        }
        void Render() override {
            }

};

#endif