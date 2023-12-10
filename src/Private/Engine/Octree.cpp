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



OctreeNode::OctreeNode(OctreeNode * parent, float penetration_depth, const Vector3D & center, float size, const std::vector<GameObject*>& objects) : center(center), size(size), objects(objects), penetration_depth(penetration_depth)
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

            children[i] = new OctreeNode(this,penetration_depth + 1, NewCenter, NewSize, newObjects);
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

                // Vérifier la collision entre obj1 et obj2
                if (obj1->IsCollidingWith(*obj2))
                {
                    // Gérer la collision entre obj1 et obj2
                    // Vous pouvez appeler une fonction de gestion de collision ici
                    // par exemple : obj1->HandleCollision(obj2);
                }
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

Octree::Octree(const Vector3D & center, float size, const std::vector<GameObject*>& objects) : Size(size), BasePosition(center), objects(objects)
{
    Build();
}



Octree::~Octree()
{
    Reset();
}

void Octree::Build()
{
    Reset();
    rootNode = new OctreeNode(nullptr,0,BasePosition,Size,objects);
}

void Octree::Reset()
{
    rootNode = nullptr;
}
