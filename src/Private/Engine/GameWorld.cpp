#include "../../Public/Engine/GameWorld.h"

#include "../../Public/GameObjects/Ground.h"
#include "../../Public/Engine/EventManager.h"
#include "../../Public/Engine/InputSystem.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../ofApp.h"
#include "../../Public/Config/Config.h"
#include "../../Public/Controller/Player.h"
#include "../../Public/GameObjects/RigidBody.h"
#include "../../Public/Particle/BlobParticle.h"
#include "../../Public/Math/ClassicSpring.h"
#include "../../Public/Math/Cable.h"
#include "../../Public/Particle/Rock.h"


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

    player = dynamic_cast<Player*>(objects.SpawnObject(new Player(Context, 10, Vector3D(0,-1000,0), Vector3D::Zero(), 10)));
    //Rock generation
    
    rockTexture.load("rock_albedo.jpg");
    for(int i = -10; i < 10; i++)
    {
        for(int j = -10; j < 10; j++)
        {
            const int randomRadius = ofRandom(20, 150);
            if(ofRandom(0,10) < 3) continue;
            Rock * rock = new Rock(&rockTexture,Vector3D(i * 500, 0, j * 500), randomRadius);
            rock->SetFaces(10);
            objects.SpawnObject(rock);
        }
    }
    objects.SpawnObject(new RigidBody(Vector3D(1,1,1), 10, player->GetPosition().Add(Vector3D(0,300,0)), Vector3D::Zero(), 10));
    player->Setup();
}

void GameWorld::Update(double DeltaTimes)
{
    objects.Update(DeltaTimes);
    
    
}

void GameWorld::Draw()
{
    
    //IMPORTANT
    player->StartPlayerSee();
    objects.Draw();
    ground.Draw();
    player->Draw();

    //IMPORTANT
    player->StopPlayerSee();
}

void GameWorld::EndPlay()
{

}

void GameWorld::OnMouseEvent(const MouseEvent& event)
{
    if(event.EventType == MouseEventType::MOUSE_MOVE)
    {
        // Obtenez la différence de position de la souris depuis la dernière frame
        const int MouseXPos = event.x;
        const int MouseYPos = event.y;

        const int deltaX = MouseXPos - LastMousePosition.GetX();
        const int deltaY = MouseYPos -  LastMousePosition.GetY();

        player->OnRotate(Vector3D(deltaX, deltaY, 0));
    
        LastMousePosition = Vector3D(ofGetWidth()/2,ofGetHeight()/2);
    }
    else if(event.EventType == MouseEventType::MOUSE_PRESSED)
    {
        if(player->IsUsingFPSCamera())
            player->Fire(this);
    }
}

void GameWorld::OnKeyboardEvent(const KeyboardEvent& event)
{
    if(event.InputType == KeyboardEventType::KEY_PRESSED)
    {
        if(event.key == Config::getChar("KEY_MOVE_FORWARD") || event.key == std::toupper(Config::getChar("KEY_MOVE_FORWARD")))
            player->StartWalkingForward();
        if(event.key == Config::getChar("KEY_MOVE_JUMP") || event.key == std::toupper(Config::getChar("KEY_MOVE_JUMP")))
            player->Jump();
        if(event.key == Config::getChar("KEY_QUIT_TPS") || event.key == std::toupper(event.key == Config::getChar("KEY_QUIT_TPS")))
            player->SwitchCameraToFPS(false);
        
    }
    if(event.InputType == KeyboardEventType::KEY_RELEASED)
    {
        if(event.key == Config::getChar("KEY_MOVE_FORWARD") || event.key == std::toupper(Config::getChar("KEY_MOVE_FORWARD")))
            player->StopWalkingForward();
        if(event.key == Config::getChar("KEY_QUIT_TPS") || event.key == std::toupper(event.key == Config::getChar("KEY_QUIT_TPS")))
            player->SwitchCameraToFPS(true);
        
    }
}

GameObjectsContainer* GameWorld::GetObjectsArray()
{
    return &objects;
}
