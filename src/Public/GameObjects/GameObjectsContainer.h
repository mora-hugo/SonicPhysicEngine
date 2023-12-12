#pragma once
#include "GameObject.h"
#include "Box.h"

class GameObjectsContainer
{
public:
    ~GameObjectsContainer();

    void Setup();
    
    void Update(double f);

  

    void Draw();

    std::vector<GameObject*>& GetObjectsArray() { return objects; }
    
    GameObject* SpawnObject(GameObject * object);
private:
    std::vector<GameObject*> objects;
};
