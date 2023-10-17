#pragma once
#include "ofCamera.h"
#include "../../Private/Engine/Interfaces/GameObject.h"
#include "../Particle/BlobParticle.h"

class Player : public GameObject
{
public:
    Player(ofCamera * Camera, BlobParticle * BlobParticle);    

    void Right();

    void Left();

    void Jump();
    
    void BeginPlay() override;
    void Update() override;
    void Draw() override;
    void EndPlay() override;

private:
    ofCamera * Camera;
    BlobParticle * BlobParticle;

    const double movement = 1000;
    const double jump = 1000;
};