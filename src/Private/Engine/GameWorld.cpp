#include "../../Public/Engine/GameWorld.h"

#include "../../Public/Engine/EventManager.h"
#include "../../Public/Engine/InputSystem.h"
#include "../../Public/Particle/ParticleFireball.h"
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

    GameObject * go = objects.SpawnObject(new BlobParticle(Vector3D(ofGetWidth()/2,-100),Vector3D(0,0),5));
    
    
    objects.SpawnObject(new Particle(INT_MAX, 0, Vector3D(ofGetWidth()/2, ofGetHeight()+200), Vector3D::Zero(), 1000,false));
    
    
    for(int i =0; i<10; ++i)
    {
        //CreateBlob(go);
        GameObject * g1 = objects.SpawnObject(new BlobParticle(go->GetPosition(),Vector3D::Zero(),5));
        Blobs.push_back(g1);
        if(Blobs.size() >= i-1)
        {
            Springs.push_back(new ClassicSpring(Blobs[i-1], g1, 5,  10, -2));
        }
        Springs.push_back(new StaticSpring(go, g1, 10,  30, -2));
    }
    Blobs.push_back(go);
    player = new Player(&Context->cam,Blobs,go);
    player->BeginPlay();
}

void GameWorld::Update(double DeltaTimes)
{
    for (Spring * spring : Springs)
    {
      spring->applyForce();
    }
    player->Update();
    objects.Update(DeltaTimes);

    //std::cout << "ground pos" << std::string(ground->GetPosition()) << std::endl;
    
}

void GameWorld::Draw()
{
    //player->Draw();
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

void GameWorld::CreateBlob(GameObject* mother, int i)
{
    Vector3D startPos = mother->GetPosition();

    startPos.SetY(startPos.GetY() - (i * 10));
    GameObject * g1 = objects.SpawnObject(new BlobParticle(startPos,Vector3D::Zero(),5));
    Blobs.push_back(g1);
    Springs.push_back(new StaticSpring(mother, g1, 20,  40, -2));
}

