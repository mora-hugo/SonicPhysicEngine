#include "../../Public/Controller/Player.h"

#include "Public/Generator/Force.h"

Player::Player(ofCamera* Camera, ::BlobParticle* BlobParticle) : Camera(Camera), BlobParticle(BlobParticle)
{
    
}

void Player::Right()
{
    
    Force right = Force(Vector3D(movement, 0, 0), 60, BlobParticle,Input);
    BlobParticle->AddForce(right);
}

void Player::Left()
{
    Force left = Force(Vector3D(-1 * movement, 0, 0), 60, BlobParticle,Input);
    BlobParticle->AddForce(left);
}

void Player::Jump()
{
    
    Force Jump = Force(Vector3D(0, jump, 0), 60, BlobParticle,Input);
    BlobParticle->AddForce(Jump);
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



