#pragma once
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "../Particle/ParticleSystem/ParticleSystem.h"
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
    ParticleSystem particleSystem;

    ofApp * Context;
};