#pragma once
#include "ofxColorPicker.h"
#include "../../Public/Math/Vector3D.h"
#include "../../Public/Math/Plane.h"
enum class CollisionType
{
    NONE,
    FACE,
    EDGE,
    VERTEX
};
class Box
{
public:
    Box();
    Box(float width, float height, float depth);
    void SetColor(ofColor color);
    void Draw();
    void Update(double f);

    //Calculer les sommets de la boite
    std::vector<Vector3D> GetVertices() const;
    std::vector<Plane> GetPlanes() const;


    bool IsCollidingWithRectangle(Box &p2, class CollisionData& OutCollisionType);
    void ResolveCollision(Box &p2, CollisionType CollisionType, class CollisionData &OutCollisionData);
    // 1 - Forward | 2 - Up |3 - Right
    void GetCollisionAtFace(Box &p2, int faceIndex, class CollisionData &OutCollisionData);
    //note perso:produit scalaire, method iscolliding with rectangle
    static Box InitBox();
    double Width = 200;
    double Height = 200;
    double Depth = 200;

    Vector3D ForwardVector = Vector3D::Forward();
    Vector3D UpVector = Vector3D::Up();
    Vector3D RightVector = Vector3D::Right();
    ofColor color;
    Vector3D position;
    Quaternion rotation = Quaternion::identity();
};
