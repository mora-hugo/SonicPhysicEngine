#include "../../Public/Engine/GameWorld.h"

#include "../../Public/GameObjects/Ground.h"
#include "../../Public/Engine/EventManager.h"
#include "../../Public/Engine/InputSystem.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../ofApp.h"
#include "../../Public/Config/Config.h"
#include "../../Public/Controller/Player.h"
#include "../../Public/GameObjects/Object3d.h"
#include "../../Public/GameObjects/Painting.h"
#include "../../Public/GameObjects/RigidBody.h"
#include "../../Public/GameObjects/Wall.h"
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
    /*
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
    */
    
    player->Setup();
    CreateMap();
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

void GameWorld::CreateMap()
{
    wallTexture.load("StoneTileTexture/Stone_2k_Albedo.jpg");

    //Nb de wall dans une direction global
    const int NbWall = 3;

    //largeur du mur pour un bon tiling
    const int WidthWall = 600;

    //========================= First Room
    //Carte symétrique à partir de 0;0;0 donc on fait des - et des + pour construire la map de chaque côté
    //back spawn 0;0;0
    for (int i= -4 ; i< NbWall+1; i++) //8 wall au total avec 4 de chaque côté
    {
        objects.SpawnObject(new Wall(&wallTexture,WidthWall,1000,100, Vector3D(i*WidthWall,0,1000)));
    }

    //front spawn 0;0;0
    for (int i= -5 ; i< NbWall+2; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,WidthWall,1000,100, Vector3D(i*WidthWall,0,-2000)));
    }

    //left spawn 0;0;0
    for (int i= -2 ; i< NbWall; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,100,1000,WidthWall, Vector3D(-2000,0,i*WidthWall)));
    }

    //right spawn 0;0;0
    for (int i= -2 ; i< NbWall; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,100,1000,WidthWall, Vector3D(2000,0,i*WidthWall)));
    }

    //======================== Corridors
    //corridor 1
    for (int i=0 ; i < 4 ; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,WidthWall,1000,100, Vector3D((-2050 +(i*-WidthWall)-(WidthWall/2)),0,-850 -WidthWall)));
    }

    for (int i=0 ; i <= 4 ; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,100,1000,WidthWall, Vector3D(-3950,0,-1800 + (i*-WidthWall))));
    }

    //corridor 2
    for (int i=0 ; i < 4 ; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,WidthWall,1000,100, Vector3D(2050 + i*WidthWall + (WidthWall/2), 0, -850 - WidthWall)));
    }

    for (int i=0 ; i <= 4 ; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,100,1000,WidthWall, Vector3D(3950,0,-1800 + (i*-WidthWall))));
    }

    //======================= Second Zone 2 rooms
    for (int i= -6 ; i< NbWall+4; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,WidthWall,1000,100, Vector3D(i*WidthWall,0,-4000)));
    }

    for (int i=-3 ; i <= 0 ; i++)
    {
        objects.SpawnObject(new Wall(&wallTexture,100,1000,WidthWall, Vector3D(0,0,-2300 + (i*WidthWall))));
    }


    //======================= Decoration Painting
    paintingTexture.load("MinecraftTexture/minecraft.jpg");
    objects.SpawnObject(new Painting(&paintingTexture,300,300,10, Vector3D(0,-250,-1950)));


    //======================= 3D Props
    //objects.SpawnObject(new Object3d("ObjectAsset/elon_musk.glb",Vector3D(1500,-100,-2500),Vector3D(0,0,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100))); // Elon Musk Easter Egg

    objects.SpawnObject(new Object3d("Props/chair.glb",Vector3D(2000,0,-2180),Vector3D(0,0,0),Vector3D(0.28,0.28,0.28),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/computer.glb",Vector3D(2000,0,-2150),Vector3D(0,0,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/Table.glb",Vector3D(1500,0,-2150),Vector3D(0,0,0),Vector3D(0.35,0.35,0.35),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_wooden_table.glb",Vector3D(1500,-150,-2500),Vector3D(0,90,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/microvax-ii.glb",Vector3D(1500,0,-2800),Vector3D(0,90,0),Vector3D(0.3,0.3,0.3),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_table_fan.glb",Vector3D(1200,0,-2800),Vector3D(0,180,0),Vector3D(0.2,0.2,0.2),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_couch.glb",Vector3D(1100,0,-3000),Vector3D(0,0,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_bed.glb",Vector3D(900,0,-3000),Vector3D(0,0,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/plant.glb",Vector3D(500,60,-2300),Vector3D(0,0,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
}