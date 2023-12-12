#pragma once
#include <vector>

#include "ofColor.h"
#include "ofMath.h"
#include "../../Public/Math/Vector3D.h"
#include "../../Public/GameObjects/GameObject.h"



struct OctreeNode
{
    Vector3D center;
    float size;

    std::vector<GameObject*> objects;
    int penetration_depth = 0;
    
    OctreeNode * children[8] = {nullptr};

    std::vector<GameObject*> GetObjectsInCube(const Vector3D& vector_3d, float new_size, const std::vector<GameObject*>& vector);
    bool IsSpherePartiallyInsideCube(const Vector3D& sphereCenter, float sphereRadius, const Vector3D& cubeCenter, float cubeHalfSize);

    
    
    OctreeNode(class Octree * parent, float penetration_depth, const Vector3D & center, float size, const std::vector<GameObject*>& objects);

    void Draw();
    void Destroy(); 
};


class Octree
{
public:
    Octree(const Vector3D & center, float size, const std::vector<GameObject*>& objects);
    ~Octree();
    bool AreAlreadyCollided(GameObject* p1, GameObject* p2);
    std::vector<std::pair<GameObject*, GameObject*>> GameObjectsCollided;
    void Draw();
    void Build();
private:
    void Reset();

    
    
public:
    constexpr static int MAX_DEPTH = 6;
    constexpr static int MAX_OBJECTS = 2;

    
    
    const inline static Vector3D OffsetTable[8] = {
        {-1, -1, -1},
        {+1, -1, -1},
        {-1, +1, -1},
        {+1, +1, -1},
        {-1, -1, +1},
        {+1, -1, +1},
        {-1, +1, +1},
        {+1, +1, +1}
    };
   
private:
    
    OctreeNode * rootNode = nullptr;
    float Size = 0;
    Vector3D BasePosition = Vector3D::Zero();
    const std::vector<GameObject*>& objects;





};

inline void Octree::Draw()
{
    rootNode->Draw();
}

