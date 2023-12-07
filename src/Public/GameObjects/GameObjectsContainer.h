#pragma once
#include "GameObject.h"
#include "Box.h"

class GameObjectsContainer
{
public:
    ~GameObjectsContainer();

    void Setup();
    
    void Update(double f);

    void SimulateCollision(GameObject& p1, GameObject& p2, double f);
    
    bool CheckOverlapOnAxis(const GameObject& p1, const GameObject& p2, const Vector3D& axis);

    bool CheckCollision(const GameObject& box1, const GameObject& box2);

    void Draw();

    std::vector<GameObject*>& GetObjectsArray() { return objects; }
    
    GameObject* SpawnObject(GameObject * object);
private:
    std::vector<GameObject*> objects;
};
