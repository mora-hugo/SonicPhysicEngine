#pragma once
#include "ofCamera.h"
#include "../Particle/BlobParticle.h"

class Player
{
public:
    Player(ofCamera * Camera,  std::vector<GameObject *>& blobs1,  std::vector<GameObject *>& blobs2, GameObject * _mother);    

    void Right();

    void Left();

    void Jump();

    void SetIsDivided(bool Divided);
    void BeginPlay();
    void Update();
    void Draw();
    void EndPlay();

private:
    ofCamera * Camera;
    std::vector<GameObject *> BlobsParticle1;
    std::vector<GameObject *> BlobsParticle2;
    GameObject * mother;
    const double movement = 160;
    const double jump = 160;
    bool bIsDivide = false;
};
