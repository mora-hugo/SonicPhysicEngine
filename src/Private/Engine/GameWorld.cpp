#include "../../Public/Engine/GameWorld.h"

#include "../../Public/Engine/EventManager.h"
#include "../../Public/Engine/InputSystem.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../ofApp.h"
#include "../../Public/Config/Config.h"
#include "../../Public/Controller/Player.h"
#include "../../Public/Particle/BlobParticle.h"
#include "../../Public/Math/ClassicSpring.h"
#include "../../Public/Math/Cable.h"


void GameWorld::BeginPlay(ofApp * Context)
{
    this->Context = Context;
    objects.Setup();

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

    
    objects.Update(DeltaTimes);

    
}

void GameWorld::Draw()
{
    objects.Draw();
}

void GameWorld::EndPlay()
{

}

void GameWorld::OnMouseEvent(const MouseEvent& event)
{
    
}

void GameWorld::OnKeyboardEvent(const KeyboardEvent& event)
{

}
