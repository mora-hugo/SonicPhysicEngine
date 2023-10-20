#pragma once
#include "ofCamera.h"
#include "../Particle/BlobParticle.h"

class Player
{
public:
    Player(ofCamera * Camera, BlobParticle * BlobParticle);    

    void Right();
    void EndRight();

    void Left();
    void EndLeft();

    void Jump();
    
    void BeginPlay();
    void Update();
    void Draw();
    void EndPlay();

private:
    ofCamera * Camera;
    BlobParticle * BlobParticle;

    const double movement = 2000;
    const double jump = 10000;
};
