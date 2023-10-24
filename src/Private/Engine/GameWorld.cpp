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

    playerParticle = objects.SpawnObject(new BlobParticle(Vector3D(ofGetWidth()/2,-100),Vector3D(0,0),20));

    //Create the planet
    ground = objects.SpawnObject(new Particle(INT_MAX, 0, Vector3D(ofGetWidth()/2, ofGetHeight()+200), Vector3D::Zero(), 1000,false));
    Particle * p = static_cast<Particle*>(ground);
    p->SetColor(ofColor::green);

    // Create the blobs
    for(int i =0; i<10; ++i)
    {
        GameObject * g1 = objects.SpawnObject(new BlobParticle(Vector3D(i*20+500,0),Vector3D::Zero(),20));
        Blobs1.push_back(g1);
    }
    // Add  the "player to the vec"
    Blobs1.push_back(playerParticle);
    for(int i =0; i<10; ++i)
    {
        GameObject * g1 = objects.SpawnObject(new BlobParticle(Vector3D(i*20+500,0),Vector3D::Zero(),20));
        Blobs2.push_back(g1);
    }

    // Adding springs 
    for(int i = 0; i < Blobs1.size(); ++i)
    {
        for(int j = i+1 ; j < Blobs1.size(); ++j)
        {
            Springs.push_back(new Cable(Blobs1[i], Blobs1[j], 0.1, NULL, -2, 80));
        }
    }

    for(int i = 0; i < Blobs2.size(); ++i)
    {
        for(int j = i+1 ; j < Blobs2.size(); ++j)
        {
            Springs.push_back(new Cable(Blobs2[i], Blobs2[j], 0.1, NULL, -2, 80));
        }
    }

    // Added temp spring (destroyed when the blob is divided)
    for(int i = 0; i < std::min(Blobs1.size(),Blobs2.size()); ++i)
    {
        for(int j = i +1; j < std::min(Blobs1.size(),Blobs2.size()); ++j)
        {
            SpringsToDestroy.push_back(new Cable(Blobs1[i], Blobs2[i], 0.1, NULL, -2, 80));
        }
    }
    
    
    player = new Player(&Context->cam,Blobs1,Blobs2,playerParticle);
    player->BeginPlay();
}

void GameWorld::Update(double DeltaTimes)
{
    for (Spring * spring : Springs)
    {
      spring->applyForce();
    }
    for (Spring * spring : SpringsToDestroy)
    {
        if(bIsDivided) break;
        spring->applyForce();
    }
    
    player->Update();
    objects.Update(DeltaTimes);

    
}

void GameWorld::Draw()
{
    objects.Draw();
}

void GameWorld::EndPlay()
{
    player->EndPlay();
    delete player;
    for(int i =0; i < Springs.size(); ++i)
    {
       delete Springs[i];
    }
}

void GameWorld::OnMouseEvent(const MouseEvent& event)
{
    
}

void GameWorld::OnKeyboardEvent(const KeyboardEvent& event)
{
    if (event.InputType == KeyboardEventType::KEY_PRESSED)
    {
        if(event.key == Config::getChar("KEY_MOVE_RIGHT"))
            player->Right();
        if(event.key == Config::getChar("KEY_MOVE_LEFT"))
            player->Left();
        if(event.key == Config::getChar("KEY_MOVE_JUMP"))
            player->Jump();
        if(event.key == Config::getChar("KEY_MOVE_DOWN"))
            player->Down();
        if(event.key == Config::getChar("KEY_MOVE_DIVIDE"))
        {
            bIsDivided = !bIsDivided;
            player->SetIsDivided(bIsDivided);
        }
    }
}

