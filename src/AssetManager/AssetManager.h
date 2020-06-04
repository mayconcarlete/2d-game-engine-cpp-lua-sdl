#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "../TextureManager/TextureManager.h"
#include "../EntityManager/EntityManager.h"
class AssetManager{
    private:
        EntityManager* manager;
        std::map<std::string, SDL_Texture*> textures;
    public:
        AssetManager(EntityManager* manager);
        AssetManager();
        void ClearData();
        void AddTexture(std::string textureId, const char* filePath);
        SDL_Texture* GetTexture(std::string textureId);
};

#endif