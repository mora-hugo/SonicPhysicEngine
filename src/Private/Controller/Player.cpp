#include "../../Public/Controller/Player.h"

#include "../../Public/Generator/Force.h"

Player::Player(ofCamera* Camera, std::vector<GameObject *>& blobs, GameObject * _mother) : Camera(Camera), mother(_mother)
{
    
    for(GameObject * BlobParticle : blobs)
    {
        BlobsParticle.push_back(BlobParticle);
    }
    
}

void Player::Right()
{
   Force right = Force(Vector3D(movement, 0, 0), 1, mother,ForceType::Input);
    mother->AddForce(right);
}

void Player::EndRight()
{
    
    Force right = Force(Vector3D(0, 1, 1), 1, mother,ForceType::Input);
    mother->AddForce(right);
    
}

void Player::Left()
{
    
    Force left = Force(Vector3D(-1 * movement, 0, 0), 1, mother,ForceType::Input);
    mother->AddForce(left);
    
}

void Player::EndLeft()
{
    
    Force left = Force(Vector3D(0, 1, 1), 1, mother,ForceType::Input);
    mother->AddForce(left);
    
}

void Player::Jump()
{
    
    Force Jump = Force(Vector3D(1, -jump, 1), 3, mother,ImpulseJump);
    mother->AddForce(Jump);
}

void Player::BeginPlay()
{
}

void Player::Update()
{
    
     Camera->setPosition(mother->GetPosition().GetX(),mother->GetPosition().GetY(),Camera->getPosition().z);
}

void Player::Draw()
{
    
}

void Player::EndPlay()
{
}



