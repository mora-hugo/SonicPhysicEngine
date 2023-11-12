#include "..\..\Public\GameObjects\Object3d.h"


Object3d::Object3d(const std::string& filepath, const Vector3D& position, const Vector3D& rotation,
    const Vector3D& scale, const Vector3D& CollisionRectangle) : GameObject(10000000, position, rotation, 0, false), CollisionRectangle(CollisionRectangle)
{
    modelLoaded.load(filepath,true);
    modelLoaded.setScale(scale.GetX(),scale.GetY(),scale.GetZ());
    modelLoaded.setRotation(0, rotation.GetX(), 1, 0, 0);
    modelLoaded.setRotation(1, rotation.GetY(), 0, 1, 0);
    modelLoaded.setRotation(2, rotation.GetZ(), 0, 0, 1);

    modelLoaded.setPosition(position.GetX(), position.GetY(), position.GetZ());

}

void Object3d::Setup()
{
    GameObject::Setup();

    
}

void Object3d::Draw()
{
    GameObject::Draw();
    modelLoaded.drawFaces();
}

void Object3d::Update(double f)
{


    
}
