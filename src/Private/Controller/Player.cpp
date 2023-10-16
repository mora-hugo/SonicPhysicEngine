#include "../../Public/Controller/Player.h"

Player::Player(ofCamera* Camera, ::BlobParticle* BlobParticle) : Camera(Camera), BlobParticle(BlobParticle)
{
    
}

void Player::Right()
{
}

void Player::Left()
{
}

void Player::Jump()
{
}

void Player::BeginPlay()
{
}

void Player::Update()
{
    Camera->setPosition(BlobParticle->GetPosition().GetX(),BlobParticle->GetPosition().GetY(),Camera->getPosition().z);
}

void Player::Draw()
{
}

void Player::EndPlay()
{
}



