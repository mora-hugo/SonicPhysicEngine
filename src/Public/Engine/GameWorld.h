#pragma once
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Octree.h"
#include "../GameObjects/GameObjectsContainer.h"
#include "../GameObjects/Ground.h"
#include "../Controller/Player.h"
#include "../Particle/ParticleSystem/ParticleSystem.h"
#include "../Math/ClassicSpring.h"
#include "../Math/StaticSpring.h"


class Player;
class ofApp;



class GameWorld
{
public:
    
    void BeginPlay(ofApp * Context);

    void Update(double DeltaTimes);

    void Draw();
    
    void EndPlay();

    void OnMouseEvent(const MouseEvent& event);

    void OnKeyboardEvent(const KeyboardEvent& event);

    GameObjectsContainer *  GetObjectsArray();


    
private:
    Vector3D LastMousePosition;
    GameObjectsContainer objects;

    ofApp * Context;

    Vector3D prev;

    Ground ground;

    Player * player = nullptr;

    ofImage rockTexture;
    ofImage wallTexture;
    ofImage sky;

    ofImage paintingTexture;
    ofImage paintingTexture2;

    ofImage paintingPropa0;
    ofImage paintingPropa1;
    ofImage paintingPropa2;
    ofImage paintingPropa3;
    ofImage paintingPropa4;
    ofImage paintingPropa5;
    Particle * particle;
    std::vector<StaticSpring* > springs;
    std::vector<GameObject* > lanternsupport;

    Octree * octree;


    void CreateMap(bool bFullmap = false);


};


