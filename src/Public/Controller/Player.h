#pragma once
#include "ofCamera.h"
#include "../Particle/BlobParticle.h"

class Player
{
public:
    Player(ofCamera * Camera,  std::vector<GameObject *>& blobs, GameObject * _mother);    

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
    std::vector<GameObject *> BlobsParticle;
    GameObject * mother;
    const double movement = 100;
    const double jump = 100;
};
