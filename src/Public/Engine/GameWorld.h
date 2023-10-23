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

    void CreateBlob(GameObject * go, int i = 0);

    
private:
    GameObjectsContainer objects;

    ofApp * Context;

    Player * player;

    std::vector<Spring*> Springs;
    std::vector<GameObject*> Blobs;

    StaticSpring test;

    GameObject * ground;
    const int nbBlob = 20; 

};
