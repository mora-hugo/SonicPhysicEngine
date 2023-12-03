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

    bool GameObjectAreEqual(GameObject * game_object);
    
    OctreeNode(OctreeNode * parent, float penetration_depth, const Vector3D & center, float size, const std::vector<GameObject*>& objects);

    void Draw();

    inline ofColor GetRandomColor()
    {
        const unsigned int Color = ofRandom(1,5);
        switch (Color)
        {
        case 1:
            return ofColor::orange;
        case 2:
            return ofColor::orangeRed;
        case 3:
            return ofColor::darkOrange;
        case 4:
            return ofColor::yellow;
        case 5:
            return ofColor::darkRed;
        default:
            break;
        }
        return ofColor::orange;

    }
};


class Octree
{
public:
    Octree(const Vector3D & center, float size, const std::vector<GameObject*>& objects);
    ~Octree();

    void Draw();
    void Build();
private:
    void Reset();

    
    
public:
    constexpr static int MAX_DEPTH = 10;
    constexpr static int MAX_OBJECTS = 1;

    
    
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
    
    OctreeNode * rootNode;
    float Size = 0;
    Vector3D BasePosition = Vector3D::Zero();
    const std::vector<GameObject*>& objects;





};

inline void Octree::Draw()
{
    rootNode->Draw();
}

