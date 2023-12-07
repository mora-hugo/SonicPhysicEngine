#include "../../Public/GameObjects/GameObjectsContainer.h"
#include "../../Public/GameObjects/Wall.h"
#include "../../Public/Controller/Player.h"
#include "../../Public/Config/Config.h"

#include <array>
#include <iostream>
#include <ostream>
#include <cmath>


GameObjectsContainer::~GameObjectsContainer()
{
}

void GameObjectsContainer::Setup()
{
}

//Détection de collision
void GameObjectsContainer::Update(double f) {
    for (unsigned int i = 0; i < objects.size(); i++) {
        
        if(objects[i]->NeedToBeDestroyed())
        {
            objects.erase(objects.begin() + i);
            continue;
        }

        objects[i]->Update(f);
        
        for (unsigned int j = i + 1; j < objects.size(); j++)
        {
            if(i != j && i < objects.size() * 2 ){ // If there is more than 2n collisions, then abandon the others
                GameObject* p1 = objects[i];
                GameObject* p2 = objects[j];

                if (CheckCollision(*p1, *p2)) {
                    // axes de séparation
                    for (int Index = 0; Index < 3; Index++) {
                        
                        Vector3D axis; //C'est l'axe de séparation

                        //Là les axes c'est des axes parallèle à X, Y et Z
                        //Il faudrait faire des axes paraalèle à :
                        //  - une face de objet 1
                        //  - Une face de objet 2
                        //  - au produit vectoriel de chaque arete de objet 1 avec chague arete de objet 2.
                        
                        if (Index == 0)
                        {
                            axis = Vector3D(1, 0, 0); 
                        } else if (Index == 1) {
                            axis = Vector3D(0, 1, 0);
                        } else {
                            axis = Vector3D(0, 0, 1);
                        }

                        if (!CheckOverlapOnAxis(*p1, *p2, axis)) {
                            //pas de collision sur cet axe
                            break;
                        }

                        //insérer algorithme de Fourier-Motzkin
                    
                    }
                    //On a une collision
                    SimulateCollision(*p1, *p2, f);
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

//Gestion de collision
void GameObjectsContainer::SimulateCollision(GameObject& p1, GameObject& p2, double f)
{
    // P1 is A / P2 is B
    CollisionData collisionData;
    const float radius = p1.GetRadius() + p2.GetRadius();
    const float distance = p1.GetPosition().Distance(p2.GetPosition());
    
    const Vector3D Penetration = p1.GetPosition().Sub(p2.GetPosition());
    collisionData.CollisionNormal = Penetration.Normalize();
    collisionData.CollisionPoint = p1.GetPosition().Add(collisionData.CollisionNormal.Multiply(p1.GetRadius()));
    collisionData.PenetrationDepth = abs(radius-distance);

    CollisionData collisionData2;
    collisionData2.CollisionNormal = collisionData.CollisionNormal.Negate();
    collisionData2.CollisionPoint = collisionData.CollisionPoint;
    collisionData2.PenetrationDepth = collisionData.PenetrationDepth;

    //Snap the targets
    Vector3D PositionOffsetP1 = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth);
    PositionOffsetP1 = PositionOffsetP1.Multiply(p2.GetMass()/(p1.GetMass()+p2.GetMass()));
    
    p1.OnCollision(&p2,collisionData);
    p2.OnCollision(&p1,collisionData2);

    Vector3D PositionOffsetP2 = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth);
    PositionOffsetP2 = PositionOffsetP2.Multiply(p1.GetMass()/(p2.GetMass()+p1.GetMass())).Negate();

    /*if(!p1.CanCollide() || !p2.CanCollide())
        continue;*/
    
    bool canContinue = false;
    if(!p1.CanCollide() || !p2.CanCollide())
    {
        canContinue = true;
    }
    
    if (canContinue)
    {
        p1.AddPosition(PositionOffsetP1);
        p2.AddPosition(PositionOffsetP2);

        // Add the impulse
        Vector3D ImpulseVectorP1;
        p1.GetImpulseFromCollision(&p2,collisionData.CollisionNormal,ImpulseVectorP1,true);

        Vector3D ImpulseVectorP2;
        p2.GetImpulseFromCollision(&p1,collisionData.CollisionNormal,ImpulseVectorP2,false);
    
        if(ImpulseVectorP1.Multiply(f).GetY() > Config::GRAVITY.GetY())
            ImpulseVectorP1.SetY(0);
        if(ImpulseVectorP2.Multiply(f).GetY() >Config::GRAVITY.GetY())
            ImpulseVectorP2.SetY(0);
    
        p1.SetVelocity(ImpulseVectorP1);
        p2.SetVelocity(ImpulseVectorP2);
    
        //std::cout << "collision ! " << std::endl;
    }    
}

//Début du cours 11
bool GameObjectsContainer::CheckOverlapOnAxis(const GameObject& p1, const GameObject& p2, const Vector3D& axis)
{    
    //Projection sur l'axe : L dans le cours
    Vector3D projectionP1 = Vector3D(p1.GetPosition()); //Il faut faire un vecteur qui fait la "taille" de l'objet.
    Vector3D projectionP2 = Vector3D(p2.GetPosition()); //Le diamètre de la boule ou la diagonale pour un cube mais je savais plus comment faire
                                                        //Diamètre de la boule ou diagonale du cube
                                                        //Si vous faites ça je crois que le reste sera bon. Normalement. Enfin je crois :D
    
    //Vérifie la collision
    float overlap = projectionP1.Distance(projectionP2);
    float totalExtent = p1.GetRadius() + p2.GetRadius();

    return overlap < totalExtent;
}

/* Ancien code de Hugo
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
                    
                    //Tracer axe de séparation
                    bool returnCheckCollision = CheckCollision(*p1, *p2);
                    std::cout << "Collision: " << (returnCheckCollision ? "true" : "false") << std::endl;

                    if (returnCheckCollision)
                    {
                        //TRouver la normale d'une face de l'objet 1 et d'une face de l'objet 2
                        
                        
                    }

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
                    
                    //std::cout << "collision ! " << std::endl;
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

*/


bool GameObjectsContainer::CheckCollision(const GameObject& p1, const GameObject& p2) {
    const bool xCollision = std::abs(p1.GetPosition().X - p2.GetPosition().X) * 2 < (p1.boxCollision.Width + p2.boxCollision.Width);
    const bool yCollision = std::abs(p1.GetPosition().Y - p2.GetPosition().Y) * 2 < (p1.boxCollision.Height + p2.boxCollision.Height);
    const bool zCollision = std::abs(p1.GetPosition().Z - p2.GetPosition().Z) * 2 < (p1.boxCollision.Depth + p2.boxCollision.Depth);

    std::cout << xCollision << " / " << yCollision << " / " << zCollision << std::endl;
    return xCollision || yCollision || zCollision;
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

