#include "../../Public/GameObjects/Painting.h"

Painting::Painting(ofImage* image, float Width, float Height, float Depth, const Vector3D& position) : ofBoxPrimitive(Width,Height,Depth), GameObject(10000000, position, Vector3D(), 0, false), texture(image)
{
    texture->getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    this->mapTexCoordsFromTexture(texture->getTexture());

}

void Painting::Setup()
{
    GameObject::Setup();
}

void Painting::Draw()
{
    GameObject::Draw();
    texture->getTexture().bind();
    draw();
    texture->getTexture().unbind();
}

void Painting::Update(double f)
{
    GameObject::Update(f);
    ofBoxPrimitive::setPosition(GetPosition());
}

void Painting::Rotate(const int degrees, const int x, const int y, const int z)
{
    rotateDeg(degrees, x, y, z);
}
