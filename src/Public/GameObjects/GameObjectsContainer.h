#pragma once
#include "GameObject.h"
#include "Box.h"

class GameObjectsContainer
{
public:
    ~GameObjectsContainer();

    void Setup();
    
    void Update(double f);

    bool CheckCollision(const GameObject& box1, const GameObject& box2);

    void Draw();

    std::vector<GameObject*>& GetObjectsArray() { return objects; }
    
    GameObject* SpawnObject(GameObject * object);
private:
    std::vector<GameObject*> objects;
};
