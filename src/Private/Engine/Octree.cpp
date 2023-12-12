#include "../../Public/Engine/Octree.h"

#include "of3dGraphics.h"
#include "ofGraphics.h"

std::vector<GameObject*> OctreeNode::GetObjectsInCube(const Vector3D& Center, float Size,
    const std::vector<GameObject*>& Objects)
{
    std::vector<GameObject*> objectsInCube;
    for(GameObject * gm : Objects) 
    {
        if(IsSpherePartiallyInsideCube(gm->GetPosition(), gm->GetRadius(), Center, Size))
        {
            objectsInCube.push_back(gm);
        }
    }
    return objectsInCube;
}

bool OctreeNode::IsSpherePartiallyInsideCube(const Vector3D& sphereCenter, float sphereRadius,
    const Vector3D& cubeCenter, float cubeHalfSize)
{
    float distance = std::sqrt(
        std::pow(sphereCenter.X - cubeCenter.X, 2) +
        std::pow(sphereCenter.Y - cubeCenter.Y, 2) +
        std::pow(sphereCenter.Z - cubeCenter.Z, 2)
    );

    // Calculer la somme du rayon de la sphère et la moitié de la longueur du côté de l'octant
    float sumRadiusHalfOctantSize = sphereRadius + cubeHalfSize;

    // Vérifier si la sphère est partiellement à l'intérieur de l'octant
    return distance < sumRadiusHalfOctantSize;
}



OctreeNode::OctreeNode(class Octree * parent, float penetration_depth, const Vector3D & center, float size, const std::vector<GameObject*>& objects) : center(center), size(size), objects(objects), penetration_depth(penetration_depth)
{

    if(penetration_depth < Octree::MAX_DEPTH && objects.size() > Octree::MAX_OBJECTS)
    {
        const float NewSize = size/2;
        // Séparer l'octree
        for(int i = 0; i < 8; i++)
        {
            //calcul de la nouvelle position
            const Vector3D NewCenter = center + Octree::OffsetTable[i].Multiply(NewSize/2);

            const std::vector<GameObject*> newObjects = GetObjectsInCube(NewCenter, NewSize, objects);

            
            if(newObjects.size() == 0)
                continue;

            children[i] = new OctreeNode(parent,penetration_depth + 1, NewCenter, NewSize, newObjects);
        }
        
    }
    else if(objects.size() >= 2)
    {
        // Check collision
        
        for (size_t i = 0; i < objects.size(); ++i)
        {
            
            for (size_t j = i + 1; j < objects.size(); ++j)
            {
                GameObject* obj1 = objects[i];
                GameObject* obj2 = objects[j];

                if(obj1->HasTag("Wall") && obj2->HasTag("Wall"))
                    continue;

               if(parent->AreAlreadyCollided(obj1,obj2))
                   continue;
                std::pair<GameObject*, GameObject*> objectPair = std::make_pair(obj1, obj2);
                
                
                // Vérifier la collision entre les sphères englobantes
                if (obj1->IsCollidingWith(*obj2))
                {
                    CollisionData collisionData;
                    CollisionData collisionData2;

                
                    bool bIsCollindingP2 = obj2->boxCollision.IsCollidingWithRectangle(obj1->boxCollision,collisionData);
                    if(bIsCollindingP2)
                    {
                        obj2->boxCollision.color = ofColor::red;
                        Vector3D PositionOffsetP1 = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth);
                        PositionOffsetP1 = PositionOffsetP1.Multiply(obj1->GetMass()/(obj2->GetMass()+obj1->GetMass()));
                        obj2->AddPosition(PositionOffsetP1);
                        Vector3D ImpulseVectorP1;
                        obj2->GetImpulseFromCollision(obj1,collisionData.CollisionNormal,ImpulseVectorP1,false);
                        if(ImpulseVectorP1.GetY() > Config::GRAVITY.GetY())
                            ImpulseVectorP1.SetY(0);

                        obj2->SetVelocity(ImpulseVectorP1);
                        
                        
                    }
                    
                    bool bIsCollindingP1 = obj1->boxCollision.IsCollidingWithRectangle(obj2->boxCollision,collisionData);
                    if(bIsCollindingP1)
                    {
                        obj1->boxCollision.color = ofColor::red;
                        Vector3D PositionOffsetP1 = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth);
                        PositionOffsetP1 = PositionOffsetP1.Multiply(obj2->GetMass()/(obj1->GetMass()+obj2->GetMass()));
                        obj1->AddPosition(PositionOffsetP1);
                        Vector3D ImpulseVectorP1;
                        obj1->GetImpulseFromCollision(obj2,collisionData.CollisionNormal,ImpulseVectorP1,true);
                        if(ImpulseVectorP1.GetY() > Config::GRAVITY.GetY())
                            ImpulseVectorP1.SetY(0);

                        obj1->SetVelocity(ImpulseVectorP1);
                    }

                    
                        
                        
                    }
                    parent->GameObjectsCollided.push_back(objectPair);
                        
                    
                    
                       /*
                         //Snap the targets
                        Vector3D PositionOffsetP1 = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth);
                        PositionOffsetP1 = PositionOffsetP1.Multiply(obj2->GetMass()/(obj1->GetMass()+obj2->GetMass()));

                        Vector3D PositionOffsetP2 = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth);
                        PositionOffsetP2 = PositionOffsetP2.Multiply(obj1->GetMass()/(obj2->GetMass()+obj1->GetMass())).Negate();

                        
                        if(!obj1->CanCollide() || !obj2->CanCollide())
                        continue;

                        parent->GameObjectsCollided.push_back(objectPair);
  
                        

                        

                      
                        obj1->OnCollision(obj2, collisionData);
                        obj2->OnCollision(obj1, collisionData);
                        
                        CollisionResolve collisionResolve;
                        collisionResolve.Offset = PositionOffsetP1;
                        obj1->collisions.push_back(collisionResolve);

                        CollisionResolve CollisionResolve2;
                        CollisionResolve2.Offset = PositionOffsetP2;
                        obj2->collisions.push_back(CollisionResolve2);
                        

                        // Add the impulse
                        Vector3D ImpulseVectorP1;
                        obj1->GetImpulseFromCollision(obj2,collisionData.CollisionNormal,ImpulseVectorP1,true);

                        Vector3D ImpulseVectorP2;
                        obj2->GetImpulseFromCollision(obj1,collisionData.CollisionNormal,ImpulseVectorP2,false);
                        
                        if(ImpulseVectorP1.GetY() > Config::GRAVITY.GetY())
                        ImpulseVectorP1.SetY(0);
                        if(ImpulseVectorP2.GetY() >Config::GRAVITY.GetY())
                        ImpulseVectorP2.SetY(0);

                        obj1->SetVelocity(0);
                        obj2->SetVelocity(0);
                    
                        obj1->SetVelocity(ImpulseVectorP1);
                        obj2->SetVelocity(ImpulseVectorP2);
                        */
                    
                }
            }
        }
        
    }


void OctreeNode::Draw()
{
    //Draw each edges of the cube
    ofNoFill();
    ofSetColor(ofColor::red);
    ofDrawBox(center, size);
    ofFill();
    ofSetColor(ofColor::white);
    
    if(objects.size() == 0) return;
    
    for(int i = 0; i < 8; i++)
    {
        if(children[i] != nullptr)
        {
            children[i]->Draw();
        }
    }
}

void OctreeNode::Destroy()
{
    for(int i = 0; i < 8; i++)
    {
        if(children[i])
        {
            children[i]->Destroy();
            delete children[i];
            children[i] = nullptr;
        }
    }
}

Octree::Octree(const Vector3D & center, float size, const std::vector<GameObject*>& objects) : Size(size), BasePosition(center), objects(objects)
{
    Build();
}



Octree::~Octree()
{
    Reset();
}

bool Octree::AreAlreadyCollided(GameObject* p1, GameObject* p2)
{
    for(std::pair<GameObject*, GameObject*> pair : GameObjectsCollided)
    {
        if((pair.first == p1 && pair.second == p2) || (pair.first == p2 && pair.second == p1))
            return true;
    }
    return false;
}

void Octree::Build()
{
    Reset();
    rootNode = new OctreeNode(this,0,BasePosition,Size,objects);
}

void Octree::Reset()
{
    GameObjectsCollided.clear();
    if(rootNode)
        rootNode->Destroy();
    rootNode = nullptr;
}
