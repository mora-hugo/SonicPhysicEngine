#include "../../Public/GameObjects/GameObjectsContainer.h"
#include "../../Public/GameObjects/Wall.h"
#include "../../Public/Controller/Player.h"
#include "../../Public/Config/Config.h"

#include <array>
#include <iostream>
#include <ostream>


GameObjectsContainer::~GameObjectsContainer()
{
}

void GameObjectsContainer::Setup()
{
}

void GameObjectsContainer::Update(double f)
{
    for(unsigned int i = 0; i < objects.size();i++)
    {
        if(objects[i]->NeedToBeDestroyed())
        {
            objects.erase(objects.begin() + i);
            continue;
        }
        objects[i]->Update(f);

            //Simulate collision for the ground
            GameObject * p1 = objects[i];
        
            if(p1->GetPosition().GetY() > 0) // collision with ground
                {
                CollisionData collisionData;
                const float radius = p1->GetRadius();
                const float distance = p1->GetPosition().Distance(Vector3D(0,0,0));
                    
                const Vector3D Penetration = p1->GetPosition().Sub(Vector3D(0,0,0));
                collisionData.CollisionNormal = Penetration.Normalize();
                collisionData.CollisionPoint = p1->GetPosition().Add(collisionData.CollisionNormal.Multiply(p1->GetRadius()));
                collisionData.PenetrationDepth = distance;

                p1->AddPosition(Vector3D(0,Penetration.Negate().GetY(),0));
            
                }
    }
}

void GameObjectsContainer::Draw()
{
    for(GameObject * object: objects)
    {
        object->Draw();
    }
}

GameObject* GameObjectsContainer::SpawnObject(GameObject* object)
{
    objects.push_back(object);
    return object;
}

