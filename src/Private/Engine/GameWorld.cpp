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

    Particle * p = particleSystem.AddParticle(new BlobParticle(Vector3D(ofGetWidth()/2,ofGetHeight()/2),Vector3D(100,0)));
    // cast particle to BlobParticle
    BlobParticle * bp = dynamic_cast<BlobParticle*>(p);
    p->SetColor(ofColor::blue);

    player = new Player(&Context->cam,bp);
    player->BeginPlay();
    
}

void GameWorld::Update(double DeltaTimes)
{
    player->Update();
    particleSystem.Update(DeltaTimes);
}

void GameWorld::Draw()
{
    ofSetColor(ofColor::red);
    ofDrawSphere(300,300,150);

    ofSetColor(ofColor::yellow);
    ofDrawSphere(550,900,150);
    player->Draw();
    particleSystem.Draw();
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
    {
    /*
    if(event.InputType == KeyboardEventType::KEY_PRESSED)
    {
        const float centerX = Context->center->x;
        const float centerY = Context->center->y;
        if(event.key == Config::getChar("KEY_THROW_BASE_PARTICLE"))
        {
            Particle * p = particleSystem.AddParticle(new ParticleFireball(20,20, Vector3D(centerX,centerY),Vector3D(Context->mouseX - centerX, Context->mouseY - centerY), Vector3D(0,150), 20));
            p->Setup();
        }
        else if(event.key == Config::getChar("KEY_THROW_FIREBALL"))
        {
            
            // Fireball
            Particle * p = particleSystem.AddParticle(new ParticleFireball(20,20, Vector3D(centerX,centerY),Vector3D(Context->mouseX - centerX, Context->mouseY - centerY), Vector3D(0,150), 20));
            p->Setup();
            Context->FireballSound.play();
        }
        else if(event.key ==  Config::getChar("KEY_THROW_FIREWORK")){
            // Firework
            Particle * p = particleSystem.AddParticle(new ParticleFirework(20,2, Vector3D(centerX,centerY),Vector3D(Context->mouseX - centerX, Context->mouseY - centerY), Vector3D(0,150), 10));
            p->Setup();
            p->ExplosionSound.setVolume(Context->Volume);
            Context->FireworkSound.play();
        }
        else if(event.key == Config::getChar("KEY_THROW_LASER")){
            // Laser
            for(int i = 0; i < 100; i++)
            {
                Particle * p = particleSystem.AddParticle(new ParticleLaser(20,1, Vector3D((centerX),centerY).Add(Vector3D(Context->mouseX - centerX, Context->mouseY - centerY).Normalize().Multiply(i)),Vector3D(Context->mouseX - centerX, Context->mouseY - centerY).Multiply(5), Vector3D(0,0), 5));
                p->Setup();
                Context->LaserSound.play();
            }
        }
    }
    */
    }
    if(event.key == Config::getChar("KEY_MOVE_RIGHT"))
        player->Right();
    if(event.key == Config::getChar("KEY_MOVE_LEFT"))
        player->Left();
    if(event.key == Config::getChar("KEY_MOVE_JUMP"))
        player->Jump(); 
}

