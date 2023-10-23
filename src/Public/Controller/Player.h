#pragma once
#include "ofCamera.h"
#include "../Particle/BlobParticle.h"

class Player
{
public:
    Player(ofCamera * Camera, GameObject * BlobParticle);    

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
    GameObject * BlobParticle;

    const double movement = 100;
    const double jump = 100;
};
