#include "../../Public/Controller/Player.h"

#include "../../Public/Generator/Force.h"

Player::Player(ofCamera* Camera, ::GameObject* BlobParticle) : Camera(Camera), BlobParticle(BlobParticle)
{
    
}

void Player::Right()
{
    
    Force right = Force(Vector3D(movement, 0, 0), 1, BlobParticle,ForceType::Input);
    BlobParticle->AddForce(right);
}

void Player::EndRight()
{
    Force right = Force(Vector3D(0, 1, 1), 1, BlobParticle,ForceType::Input);
    BlobParticle->AddForce(right);
}

void Player::Left()
{
    Force left = Force(Vector3D(-1 * movement, 0, 0), 1, BlobParticle,ForceType::Input);
    BlobParticle->AddForce(left);
}

void Player::EndLeft()
{
    Force left = Force(Vector3D(0, 1, 1), 1, BlobParticle,ForceType::Input);
    BlobParticle->AddForce(left);
}

void Player::Jump()
{
    Force Jump = Force(Vector3D(1, -jump, 1), 3, BlobParticle,ImpulseJump);
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



