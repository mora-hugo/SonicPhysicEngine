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
        for(unsigned int j = i + 1; j < objects.size(); j++)
        {
            if(i != j && i < objects.size() * 2 ) // If there is more than 2n collisions, then abandon the others
            {
                GameObject * p1 = objects[i];
                GameObject * p2 = objects[j];
                if(p1->IsCollidingWith(*p2))
                {
                    // P1 is A / P2 is B
                    CollisionData collisionData;
                    const float radius = p1->GetRadius() + p2->GetRadius();
                    const float distance = p1->GetPosition().Distance(p2->GetPosition());
                    
                    const Vector3D Penetration = p1->GetPosition().Sub(p2->GetPosition());
                    collisionData.CollisionNormal = Penetration.Normalize();
                    collisionData.CollisionPoint = p1->GetPosition().Add(collisionData.CollisionNormal.Multiply(p1->GetRadius()));
                    collisionData.PenetrationDepth = abs(radius-distance);
    
                    CollisionData collisionData2;
                    collisionData2.CollisionNormal = collisionData.CollisionNormal.Negate();
                    collisionData2.CollisionPoint = collisionData.CollisionPoint;
                    collisionData2.PenetrationDepth = collisionData.PenetrationDepth;
                    

                    collisionData.CollisionNormal;
                    //Tracer axe de séparation

                    

                    //Snap the targets

                    Vector3D PositionOffsetP1 = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth);
                    PositionOffsetP1 = PositionOffsetP1.Multiply(p2->GetMass()/(p1->GetMass()+p2->GetMass()));

                    p1->OnCollision(p2,collisionData);
                    p2->OnCollision(p1,collisionData2);

                    Vector3D PositionOffsetP2 = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth);
                    PositionOffsetP2 = PositionOffsetP2.Multiply(p1->GetMass()/(p2->GetMass()+p1->GetMass())).Negate();

                    if(!p1->CanCollide() || !p2->CanCollide())
                        continue;
                    
                    p1->AddPosition(PositionOffsetP1);
                    p2->AddPosition(PositionOffsetP2);

                    // Add the impulse
                    Vector3D ImpulseVectorP1;
                    p1->GetImpulseFromCollision(p2,collisionData.CollisionNormal,ImpulseVectorP1,true);

                    Vector3D ImpulseVectorP2;
                    p2->GetImpulseFromCollision(p1,collisionData.CollisionNormal,ImpulseVectorP2,false);

                    
                    
                    if(ImpulseVectorP1.Multiply(f).GetY() > Config::GRAVITY.GetY())
                        ImpulseVectorP1.SetY(0);
                    if(ImpulseVectorP2.Multiply(f).GetY() >Config::GRAVITY.GetY())
                        ImpulseVectorP2.SetY(0);
                    
                    
                    p1->SetVelocity(ImpulseVectorP1);
                    p2->SetVelocity(ImpulseVectorP2);
                    
                    std::cout << "collision ! " << std::endl;
                }
                
            }

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

