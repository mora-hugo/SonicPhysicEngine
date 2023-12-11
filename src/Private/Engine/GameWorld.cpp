#include "../../Public/Engine/GameWorld.h"

#include "../../Public/GameObjects/Ground.h"
#include "../../Public/Engine/EventManager.h"
#include "../../Public/Engine/InputSystem.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../ofApp.h"
#include "../../Public/Config/Config.h"
#include "../../Public/Controller/Player.h"
#include "../../Public/GameObjects/Ennemi.h"
#include "../../Public/GameObjects/Object3d.h"
#include "../../Public/GameObjects/Painting.h"
#include "../../Public/GameObjects/Cube.h"
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

    player = dynamic_cast<Player*>(objects.SpawnObject(new Player(Context, 10, Vector3D(0,0,-800), Vector3D::Zero(), 80)));
    rockTexture.load("rock_albedo.jpg");
    player->Setup();
    CreateMap(false);

   
    octree = new Octree(Vector3D::Zero(), 10000, objects.GetObjectsArray());
    std::cout << "octree created" << std::endl;

}

void GameWorld::Update(double DeltaTimes)
{
    objects.Update(DeltaTimes);
    for(auto & obj : objects.GetObjectsArray())
    {
        obj->boxCollision.color = ofColor::white;
    }
    octree->Build();
    
    for(auto spring : springs)
    {
        spring->applyForce();
    }
    
}

void GameWorld::Draw()
{
    
    //IMPORTANT
    player->StartPlayerSee();
    objects.Draw();
    ground.Draw();
    player->Draw();
    octree->Draw(); //Comment this to hide the lines of the octree (prevent the draw)

    //IMPORTANT
    player->StopPlayerSee();
}

void GameWorld::EndPlay()
{
    
    lanternsupport.clear();
    springs.clear();
    delete octree;
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
        if(event.key == Config::getChar("KEY_MOVE_BACKWARD") || event.key == std::toupper(Config::getChar("KEY_MOVE_BACKWARD")))
            player->StartWalkingBackward();
        if(event.key == Config::getChar("KEY_MOVE_LEFT") || event.key == std::toupper(Config::getChar("KEY_MOVE_LEFT")))
            player->StartStrafingLeft();
        if(event.key == Config::getChar("KEY_MOVE_RIGHT") || event.key == std::toupper(Config::getChar("KEY_MOVE_RIGHT")))
            player->StartStrafingRight();
        if(event.key == Config::getChar("KEY_MOVE_JUMP") || event.key == std::toupper(Config::getChar("KEY_MOVE_JUMP")))
            player->Jump();
        if(event.key == Config::getChar("KEY_QUIT_TPS") || event.key == std::toupper(event.key == Config::getChar("KEY_QUIT_TPS")))
            player->SwitchCameraToFPS(false);
        if(event.key == Config::getChar("KEY_RELOAD") || event.key == std::toupper(Config::getChar("KEY_RELOAD")))
            player->Reload();
        
    }
    if(event.InputType == KeyboardEventType::KEY_RELEASED)
    {
        if(event.key == Config::getChar("KEY_MOVE_FORWARD") || event.key == std::toupper(Config::getChar("KEY_MOVE_FORWARD")))
            player->StopWalkingForward();
        if(event.key == Config::getChar("KEY_MOVE_BACKWARD") || event.key == std::toupper(Config::getChar("KEY_MOVE_BACKWARD")))
            player->StopWalkingBackward();
        if(event.key == Config::getChar("KEY_MOVE_LEFT") || event.key == std::toupper(Config::getChar("KEY_MOVE_LEFT")))
            player->StopStrafingLeft();
        if(event.key == Config::getChar("KEY_MOVE_RIGHT") || event.key == std::toupper(Config::getChar("KEY_MOVE_RIGHT")))
            player->StopStrafingRight();
        if(event.key == Config::getChar("KEY_QUIT_TPS") || event.key == std::toupper(event.key == Config::getChar("KEY_QUIT_TPS")))
            player->SwitchCameraToFPS(true);
        
    }
}

GameObjectsContainer* GameWorld::GetObjectsArray()
{
    return &objects;
}

void GameWorld::CreateMap(bool bFullmap)
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
    Painting* painting = new Painting(&paintingTexture,300,300,10, Vector3D(0,-250,-1950));
    /*
    objects.SpawnObject(painting);
    painting->Rotate(180,0,0,1);
*/

    paintingTexture2.load("CarpetTexture/CarpetTexture.jpeg");
    painting = new Painting(&paintingTexture2,400,1300,5, Vector3D(0,-2,-100));
    objects.SpawnObject(painting);
    painting->Rotate(90,1,0,0);

    Ennemi * ennemi = new Ennemi("Ennemis/WallE.glb", Vector3D(0,-2000,-400), Vector3D(0.4,0.4,0.4));
    ennemi->SetTargetGameObject(player);
    ennemi->FollowTargetOn(true);
    objects.SpawnObject(ennemi);

    Ennemi * ennemi2 = new Ennemi("Ennemis/WallE.glb", Vector3D(2000,-2000,-3000), Vector3D(0.4,0.4,0.4));
    ennemi2->SetTargetGameObject(player);
    ennemi2->FollowTargetOn(true);
    objects.SpawnObject(ennemi2);

    Ennemi * ennemi3 = new Ennemi("Ennemis/WallE.glb", Vector3D(-2000,-2000,-3000), Vector3D(0.4,0.4,0.4));
    ennemi3->SetTargetGameObject(player);
    ennemi3->FollowTargetOn(true);
    objects.SpawnObject(ennemi3);






    //======================= 3D Props
    // objects.SpawnObject(new Object3d("ObjectAsset/elon_musk.glb",Vector3D(1500,-20,-2500),Vector3D(0,0,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100))); // Elon Musk Easter Egg

    if(!bFullmap) return;
    //======================= Lab Room
    objects.SpawnObject(new Object3d("ObjectAsset/computer.glb",Vector3D(2000,0,-2150),Vector3D(0,0,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
        objects.SpawnObject(new Object3d("Props/chair.glb",Vector3D(2000,0,-2180),Vector3D(0,0,0),Vector3D(0.28,0.28,0.28),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/computer.glb",Vector3D(500,0,-2150),Vector3D(0,0,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
        objects.SpawnObject(new Object3d("Props/chair.glb",Vector3D(500,0,-2180),Vector3D(0,0,0),Vector3D(0.28,0.28,0.28),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/carbon_server_console.glb",Vector3D(1100,-280,-2120),Vector3D(0,0,0),Vector3D(0.5,0.5,0.5),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/carbon_server_console.glb",Vector3D(1400,-280,-3850),Vector3D(0,180,0),Vector3D(0.5,0.5,0.5),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/server_armoir.glb",Vector3D(1400,0,-2120),Vector3D(0,0,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/sewrver_armoir.glb",Vector3D(2500,0,-3850),Vector3D(0,180,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/server_armoir.glb",Vector3D(1100,0,-3850),Vector3D(0,180,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
    //
    objects.SpawnObject(new Object3d("ObjectAsset/school_board.glb",Vector3D(3000,-150,-3950),Vector3D(0,-90,0),Vector3D(1.2,1.2,1.2),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/school_board.glb",Vector3D(3900,-150,-3000),Vector3D(0,0,0),Vector3D(1.2,1.2,1.2),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/coat_rack.glb",Vector3D(3700,-150,-3850),Vector3D(0,0,0),Vector3D(0.8,0.8,0.8),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/old_wooden_table.glb",Vector3D(2000,-140,-3800),Vector3D(0,90,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
        objects.SpawnObject(new Object3d("ObjectAsset/oscillograph.glb",Vector3D(1900,-150,-3800),Vector3D(0,160,0),Vector3D(0.25,0.25,0.25),Vector3D(100,100,100)));
        objects.SpawnObject(new Object3d("ObjectAsset/power_supply_device.glb",Vector3D(2130,-150,-3820),Vector3D(0,200,0),Vector3D(0.25,0.25,0.25),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/old_wooden_table.glb",Vector3D(500,-140,-3800),Vector3D(0,90,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
        objects.SpawnObject(new Object3d("ObjectAsset/wood_chair.glb",Vector3D(500,0,-3500),Vector3D(0,20,0),Vector3D(0.4,0.4,0.4),Vector3D(100,100,100)));
        objects.SpawnObject(new Object3d("ObjectAsset/old_table_fan.glb",Vector3D(620,-150,-3800),Vector3D(0,-50,0),Vector3D(0.3,0.3,0.3),Vector3D(100,100,100)));
        objects.SpawnObject(new Object3d("ObjectAsset/paper_tablet.glb",Vector3D(480,-150,-3820),Vector3D(270,180,180),Vector3D(0.2,0.2,0.2),Vector3D(100,100,100)));


    //======================= Employee Room (-3950 max x | -4000 max z)

    objects.SpawnObject(new Object3d("ObjectAsset/old_couch.glb",Vector3D(-2500,0,-2180),Vector3D(0,0,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_couch.glb",Vector3D(-1500,0,-2180),Vector3D(0,0,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_couch.glb",Vector3D(-1500,0,-3850),Vector3D(0,180,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/old_bed.glb",Vector3D(-450,0,-2650),Vector3D(0,90,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_bed.glb",Vector3D(-450,0,-3450),Vector3D(0,90,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/plant.glb",Vector3D(-2000,60,-2200),Vector3D(0,0,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/plant.glb",Vector3D(-3000,60,-2200),Vector3D(0,0,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/plant.glb",Vector3D(-1000,60,-2200),Vector3D(0,0,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/plant.glb",Vector3D(-1000,60,-3850),Vector3D(0,0,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/plant.glb",Vector3D(-2700,60,-3850),Vector3D(0,0,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/retro_coca-cola_fridge.glb",Vector3D(-2500,0,-3950),Vector3D(0,180,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/sempai_coffee_machine.glb",Vector3D(-2000,-180,-3850),Vector3D(0,-90,0),Vector3D(0.65,0.65,0.65),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/steel_locker.glb",Vector3D(-3800,-280,-3600),Vector3D(0,90,0),Vector3D(0.55,0.55,0.55),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/steel_locker.glb",Vector3D(-3800,-280,-3500),Vector3D(0,90,0),Vector3D(0.55,0.55,0.55),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/steel_locker.glb",Vector3D(-3800,-280,-3400),Vector3D(0,90,0),Vector3D(0.55,0.55,0.55),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/steel_locker.glb",Vector3D(-3800,-280,-3300),Vector3D(0,90,0),Vector3D(0.55,0.55,0.55),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/steel_locker.glb",Vector3D(-3800,-280,-3200),Vector3D(0,90,0),Vector3D(0.55,0.55,0.55),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/old_wooden_table.glb",Vector3D(-3300,-140,-3800),Vector3D(0,90,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/wood_chair.glb",Vector3D(-3350,0,-3700),Vector3D(0,20,0),Vector3D(0.4,0.4,0.4),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/wood_chair.glb",Vector3D(-3200,0,-3600),Vector3D(0,-20,0),Vector3D(0.4,0.4,0.4),Vector3D(100,100,100)));

    //======================= Propaganda
    paintingPropa0.load("PropagandaTexture/propa_young.jpg");
    painting = new Painting(&paintingPropa0,100,200,5, Vector3D(-50,-300,-3370));
    objects.SpawnObject(painting);
    painting->Rotate(180,0,0,1);
    painting->Rotate(90,0,1,0);
    
    paintingPropa1.load("PropagandaTexture/propa_genie.jpg");
    painting = new Painting(&paintingPropa1,100,200,5, Vector3D(-50,-300,-2570));
    objects.SpawnObject(painting);
    painting->Rotate(180,0,0,1);
    painting->Rotate(90,0,1,0);
    
    paintingPropa2.load("PropagandaTexture/propa_wcdi.jpg"); //we can do it
    painting = new Painting(&paintingPropa2,100,200,5, Vector3D(-2500,-300,-2070));
    objects.SpawnObject(painting);
    painting->Rotate(180,0,0,1);
    
    paintingPropa4.load("PropagandaTexture/propa_monkey.jpg");
    painting = new Painting(&paintingPropa4,100,200,5, Vector3D(-1500,-300,-2070));
    objects.SpawnObject(painting);
    painting->Rotate(180,0,0,1);
    
    paintingPropa3.load("PropagandaTexture/propa_work.jpg"); //medecine
    painting = new Painting(&paintingPropa3,400,200,5, Vector3D(-1500,-300,-3920));
    objects.SpawnObject(painting);
    painting->Rotate(180,0,0,1);
    
    paintingPropa5.load("PropagandaTexture/propa_medecine.jpg");
    painting = new Painting(&paintingPropa5,100,200,5, Vector3D(-3900,-300,-2500));
    objects.SpawnObject(painting);
    painting->Rotate(180,0,0,1);
    painting->Rotate(90,0,1,0);

    //======================= Reception
    objects.SpawnObject(new Object3d("ObjectAsset/reception_desk.glb",Vector3D(0,-150,-1600),Vector3D(0,180,0),Vector3D(2,2,2),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/reception_door_metal.glb",Vector3D(0,-180,950),Vector3D(0,0,0),Vector3D(0.8,0.8,0.8),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/plant.glb",Vector3D(-1800,60,750),Vector3D(0,0,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/plant.glb",Vector3D(1800,60,750),Vector3D(0,0,0),Vector3D(0.6,0.6,0.6),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_couch.glb",Vector3D(1800,0,-100),Vector3D(0,-90,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/old_couch.glb",Vector3D(-1800,0,-100),Vector3D(0,90,0),Vector3D(0.9,0.9,0.9),Vector3D(100,100,100)));
    
    
    objects.SpawnObject(new Object3d("ObjectAsset/retro_coca-cola_fridge.glb",Vector3D(-500,0,950),Vector3D(0,0,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/sempai_coffee_machine.glb",Vector3D(-1200,-180,850),Vector3D(0,90,0),Vector3D(0.65,0.65,0.65),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/retro_coca-cola_fridge.glb",Vector3D(1900,0,-1000),Vector3D(0,-90,0),Vector3D(0.7,0.7,0.7),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/sempai_coffee_machine.glb",Vector3D(1800,-180,-1050),Vector3D(0,0,0),Vector3D(0.65,0.65,0.65),Vector3D(100,100,100)));
    
    objects.SpawnObject(new Object3d("ObjectAsset/greek_pillar.glb",Vector3D(-100,150,0),Vector3D(0,0,0),Vector3D(1,1,1),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/greek_pillar.glb",Vector3D(-950,150,0),Vector3D(0,0,0),Vector3D(1,1,1),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/greek_pillar.glb",Vector3D(-100,150,700),Vector3D(0,0,0),Vector3D(1,1,1),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/greek_pillar.glb",Vector3D(-950,150,700),Vector3D(0,0,0),Vector3D(1,1,1),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/greek_pillar.glb",Vector3D(-100,150,-700),Vector3D(0,0,0),Vector3D(1,1,1),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/greek_pillar.glb",Vector3D(-950,150,-700),Vector3D(0,0,0),Vector3D(1,1,1),Vector3D(100,100,100)));
    
    
    objects.SpawnObject(new Object3d("ObjectAsset/globe.glb",Vector3D(-1700,0,-1000),Vector3D(0,0,0),Vector3D(0.65,0.65,0.65),Vector3D(100,100,100)));
    objects.SpawnObject(new Object3d("ObjectAsset/marble_statue.glb",Vector3D(1100,0,800),Vector3D(0,0,0),Vector3D(0.65,0.65,0.65),Vector3D(100,100,100)));


}