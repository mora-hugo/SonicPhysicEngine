#include "../../Public/Controller/Player.h"

#include "../../Public/Generator/Force.h"

Player::Player(ofCamera* Camera, std::vector<GameObject *>& blobs1,  std::vector<GameObject *>& blobs2, GameObject * _mother) : Camera(Camera), mother(_mother)
{
    
    for(GameObject * BlobParticle : blobs1)
    {
        BlobsParticle1.push_back(BlobParticle);
    }

    for(GameObject * BlobParticle : blobs2)
    {
        BlobsParticle2.push_back(BlobParticle);
    }
    
}

void Player::Right()
{
    for(GameObject * BlobParticle : BlobsParticle1)
    {
        Force right = Force(Vector3D(movement, 0, 0), 1,ForceType::Input);
        BlobParticle->AddForce(right);
    }
    if(bIsDivide) return;
    for(GameObject * BlobParticle : BlobsParticle2)
    {
        Force right = Force(Vector3D(movement, 0, 0), 1,ForceType::Input);
        BlobParticle->AddForce(right);
    }
   
}



void Player::Left()
{
    for(GameObject * BlobParticle : BlobsParticle1)
    {
        Force left = Force(Vector3D(-1 * movement, 0, 0), 1,ForceType::Input);
        BlobParticle->AddForce(left);
    }
    if(bIsDivide) return;
    for(GameObject * BlobParticle : BlobsParticle2)
    {
        Force left = Force(Vector3D(-1 * movement, 0, 0), 1,ForceType::Input);
        BlobParticle->AddForce(left);
    }
}



void Player::Jump()
{
    for(GameObject * BlobParticle : BlobsParticle1)
    {
        Force Jump = Force(Vector3D(1, -jump, 1), 3,ImpulseJump);
        BlobParticle->AddForce(Jump);
    }
    if(bIsDivide) return;
    for(GameObject * BlobParticle : BlobsParticle2)
    {
        Force Jump = Force(Vector3D(1, -jump, 1), 3,ImpulseJump);
        BlobParticle->AddForce(Jump);
    }
}

void Player::Down()
{
    for(GameObject * BlobParticle : BlobsParticle1)
    {
        Force Jump = Force(Vector3D(1, jump, 1), 3,ImpulseJump);
        BlobParticle->AddForce(Jump);
    }
    if(bIsDivide) return;
    for(GameObject * BlobParticle : BlobsParticle2)
    {
        Force Jump = Force(Vector3D(1, jump, 1), 3,ImpulseJump);
        BlobParticle->AddForce(Jump);
    }
}

void Player::SetIsDivided(bool Divided)
{
    bIsDivide = Divided;
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



