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

    GameObject * go = objects.SpawnObject(new BlobParticle(Vector3D(ofGetWidth()/2,-100),Vector3D(0,0)));

    
    GameObject * g1 = objects.SpawnObject(new Particle(10,1,Vector3D(50,50),Vector3D::Zero(),50));
    // cast particle to BlobParticle
    BlobParticle * bp = dynamic_cast<BlobParticle*>(go);
    bp->SetColor(ofColor::blue);


    
    
    GameObject * ground = objects.SpawnObject(new Particle(INT_MAX, 0, Vector3D(ofGetWidth()/2, ofGetHeight()+200), Vector3D::Zero(), 1000,false));
    
    player = new Player(&Context->cam,bp);
    for(int i =0; i<1; ++i)
    {
        CreateBlob(bp);
    }
    player->BeginPlay();
}

void GameWorld::Update(double DeltaTimes)
{
    for (StaticSpring * spring : Springs)
    {
        spring->applyForce();
    }
    player->Update();
    objects.Update(DeltaTimes);
    
   
}

void GameWorld::Draw()
{
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

void GameWorld::CreateBlob(BlobParticle* mother)
{
    Vector3D startPos = mother->GetPosition();

    int rx = ofRandom(10,20);
    int ry = ofRandom(10,20);
    int rnegate = ofRandom(0,1);

    if (rnegate == 0)
    {
        startPos.Add(Vector3D(rx , ry, 0));
    } 
    {
        startPos.Add(Vector3D(-rx , -ry, 0));
    }
    GameObject * g1 = objects.SpawnObject(new Particle(10,1,startPos,Vector3D::Zero(),50));

    Springs.push_back(new StaticSpring(mother, g1, 20,  50, -2));
}

