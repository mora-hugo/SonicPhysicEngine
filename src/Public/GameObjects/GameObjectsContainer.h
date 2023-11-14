#pragma onceD
#include "GameObject.h"

class GameObjectsContainer
{
public:
    ~GameObjectsContainer();

    void Setup();
    
    void Update(double f);

    void Draw();


    
    GameObject* SpawnObject(GameObject * object);
private:
    std::vector<GameObject*> objects;
};
