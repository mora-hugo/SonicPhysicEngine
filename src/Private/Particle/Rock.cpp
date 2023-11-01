#include "../../Public/Particle/Rock.h"

Rock::Rock(ofImage * image, const Vector3D& Position, int Radius) : Particle(100000, 0, Position, Vector3D::Zero(), Radius, false)
{
    texture = image;
    texture->getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    this->mapTexCoordsFromTexture(texture->getTexture());
}

void Rock::Setup()
{
    Particle::Setup();
}

void Rock::Draw() 
{
    texture->getTexture().bind();
    Particle::Draw();
    texture->getTexture().unbind();
}

void Rock::Update(double f)
{
    Particle::Update(f);
}
