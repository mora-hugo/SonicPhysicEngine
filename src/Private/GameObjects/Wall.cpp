﻿#include "../../Public/GameObjects/Wall.h"



Wall::Wall(ofImage * image,float Width, float Height, float Depth, const Vector3D& position) : ofBoxPrimitive(Width,Height,Depth), GameObject(10000000, position, Vector3D(), 0, false), texture(image)
{
    texture->getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    this->mapTexCoordsFromTexture(texture->getTexture());
}

void Wall::Setup()
{
    GameObject::Setup();
}

void Wall::Draw()
{
    GameObject::Draw();
    texture->getTexture().bind();
    draw();
    texture->getTexture().unbind();
}

void Wall::Update(double f)
{
    
    GameObject::Update(f);
    ofBoxPrimitive::setPosition(GetPosition());
}