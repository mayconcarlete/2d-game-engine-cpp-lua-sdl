#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "../EntityManager/EntityManager.h"
#include"../Entity/Entity.h"

class EntityManager;
class Component;

class Entity{
    private:
        EntityManager& manager;
        bool isActive;
        std::map<const std::type_info*, Component*> componentTypeMap;
    public:
        std::vector<Component*> components;
        std::string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
        void ListAllComponents();
        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args){
            T* newComponent(new T(std::forward<TArgs>(args)...));
            newComponent->className = typeid(T).name();
            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentTypeMap[&typeid(*newComponent)] = newComponent;
            newComponent->Initialize();
            return *newComponent;
        }
        template <typename T>
        T* GetComponent(){
            return static_cast<T*>(componentTypeMap[&typeid(T)]);
        }
        template <typename T>
        bool HasComponent() const {
            bool result = false;
            for(auto& componentType: componentTypeMap){
                std::cout<< "Component Type: "<< componentType.first <<"\n";
               // std::cout<< "Component Type2: "<< componentType.first <<"\n";
                std::cout<<"Component Address: "<< &typeid(T*) <<"\n";
                std::cout<<"Component Address: "<< &typeid(T) <<"\n";
                std::cout<<"Component Address: "<< &typeid(T) <<"\n";
               // std::cout<<"Component T: "<<typeid(T*).name()<<"\n";
                
                //std::cout<<"Nome: " << typeid(&componentType.first).name() <<"\n";
                //std::cout<< "Por type:"<<&typeid(T) <<"\n";
                //std::cout<< typeid(&(componentType.first)).name() <<"\n";
            }
            std::cout<<result<<"\n";
        }
};

#endif