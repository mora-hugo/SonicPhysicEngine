#pragma onceD
#include "GameObject.h"

class GameObjectsContainer
{
public:
    ~GameObjectsContainer();

    void Setup();
    
    void Update(double f);

    void Draw();


    bool CheckCollision(class Player * player,class Wall * wall);
    
    GameObject* SpawnObject(GameObject * object);
private:
    std::vector<GameObject*> objects;
};
