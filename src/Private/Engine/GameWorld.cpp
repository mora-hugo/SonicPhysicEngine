#include "../../Public/Engine/GameWorld.h"

#include "../../Public/Engine/EventManager.h"
#include "../../Public/Engine/InputSystem.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../Public/Particle/ParticleFirework.h"
#include "../../Public/Particle/ParticleLaser.h"
#include "../../ofApp.h"
#include "../../Public/Config/Config.h"
#include "../../Public/Controller/Player.h"
#include "../../Public/Particle/BlobParticle.h"
#include "../../Public/Math/ClassicSpring.h"


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

    GameObject * go = objects.SpawnObject(new BlobParticle(Vector3D(ofGetWidth()/2,ofGetHeight()/2),Vector3D(0,0)));

    
    GameObject * g1 = objects.SpawnObject(new Particle(10,1,Vector3D(50,50),Vector3D::Zero(),Vector3D::Zero(),50));
    // cast particle to BlobParticle
    BlobParticle * bp = dynamic_cast<BlobParticle*>(go);
    bp->SetColor(ofColor::blue);
    //spring = ClassicSpring(BlobParticule1,BlobParticule2,20,80,-2);
    
    player = new Player(&Context->cam,bp);
    player->BeginPlay();
}

void GameWorld::Update(double DeltaTimes)
{
    //spring.applyForce();
    player->Update();
    objects.Update(DeltaTimes);
}

void GameWorld::Draw()
{
    ofSetColor(ofColor::red);
    ofDrawSphere(300,300,150);

    ofSetColor(ofColor::yellow);
    ofDrawSphere(550,900,150);
    player->Draw();
    objects.Draw();
}

void GameWorld::EndPlay()
{
    player->EndPlay();
    delete player;
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
    }
}

