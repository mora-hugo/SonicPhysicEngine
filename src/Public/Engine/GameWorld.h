#pragma once
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "../GameObjects/GameObjectsContainer.h"
#include "../Particle/ParticleSystem/ParticleSystem.h"
#include "../Math/ClassicSpring.h"
#include "../Math/StaticSpring.h"

class Player;
class ofApp;



class GameWorld
{
public:
    
    void BeginPlay(ofApp * Context);

    void Update(double DeltaTimes);

    void Draw();
    
    void EndPlay();

    void OnMouseEvent(const MouseEvent& event);

    void OnKeyboardEvent(const KeyboardEvent& event);

    void CreateBlob(BlobParticle *mother);

    
private:
    GameObjectsContainer objects;

    ofApp * Context;

    Player * player;

    std::vector<StaticSpring> Springs;
    std::vector<BlobParticle> Blobs;

    const int nbBlob = 20; 

};
