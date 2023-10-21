#pragma once
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "../GameObjects/GameObjectsContainer.h"
#include "../Particle/ParticleSystem/ParticleSystem.h"
#include "ClassicSpring.h"
#include "StaticSpring.h"

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

    
private:
    GameObjectsContainer objects;

    ofApp * Context;

    Player * player;

    ClassicSpring spring;

    StaticSpring staticSpring;

};
