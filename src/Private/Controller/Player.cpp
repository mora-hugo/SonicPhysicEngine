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
    BlobParticle->modifyVelocity(0,1,0);
}

void Player::Left()
{
    Force left = Force(Vector3D(-1 * movement, 0, 0), 1, BlobParticle,ForceType::Input);
    BlobParticle->AddForce(left);
}

void Player::EndLeft()
{
    BlobParticle->modifyVelocity(0,1,0);
}

void Player::Jump()
{
    Force Jump = Force(Vector3D(0, -jump, 0), 3, BlobParticle,InputJump);
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



