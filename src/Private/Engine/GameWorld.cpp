#include "../../Public/Engine/GameWorld.h"

#include "../../Public/Engine/EventManager.h"
#include "../../Public/Engine/InputSystem.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../ofApp.h"


void GameWorld::BeginPlay(ofApp * Context)
{
    this->Context = Context;
    particleSystem.Setup();

    // Subscribe to events
    EventManager::MouseEvent.subscribe([=](const MouseEvent& event) {
        OnMouseEvent(event);
    });

    EventManager::KeyboardEvent.subscribe([=](const KeyboardEvent& event) {
        OnKeyboardEvent(event);
    });
}

void GameWorld::Update(double DeltaTimes)
{
    particleSystem.Update(DeltaTimes);
}

void GameWorld::Draw()
{
    particleSystem.Draw();
}

void GameWorld::EndPlay()
{
    
}

void GameWorld::OnMouseEvent(const MouseEvent& event)
{
    
}

void GameWorld::OnKeyboardEvent(const KeyboardEvent& event)
{
    if(event.key == 'c' && event.InputType == KeyboardEventType::KEY_PRESSED)
    {
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,20, Vector3D(Context->center->x,Context->center->y),Vector3D(Context->mouseX - Context->center->x, Context->mouseY - Context->center->y), Vector3D(0,150), 20));
        p->Setup();
    }
}
