#pragma once
#include "FPSCamera.h"
#include "ofCamera.h"
#include "ofPixels.h"
#include "ofImage.h"
#include "ofxAssimpModelLoader.h"
#include "../Particle/BlobParticle.h"

class Player : public GameObject
{

public:
    
    Player(ofApp * Context, const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), int SphereRadius = 10);
    void OnRotate(const Vector3D& DeltaRot);
    void Setup() override;
    void Draw() override;
    void Update(double f) override;

    void Jump();
    void StartWalkingForward();
    void StopWalkingForward();

    FPSCamera * GetCamera() const;

    Vector3D GetLaunchPoint();
    

private:
    FPSCamera * Camera;

    Vector3D CameraOffset{0, 200, 0};
    Vector3D WeaponOffset{0, 10, 0};

    bool bIsGoingForward = false;

    float Speed = 1000;
    float JumpForce = 2000;
    ofxAssimpModelLoader Weapon;
    ofImage WeaponTexture;
};
