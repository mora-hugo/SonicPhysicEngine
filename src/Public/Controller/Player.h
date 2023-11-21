#pragma once
#include "FPSCamera.h"
#include "ofCamera.h"
#include "ofPixels.h"
#include "ofImage.h"
#include "ofTrueTypeFont.h"
#include "ofxAssimpModelLoader.h"
#include "TPSCamera.h"
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
    void Reload();
    void Fire(class GameWorld * Context);
    void StartWalkingForward();
    void StopWalkingForward();

    void StartWalkingBackward();
    void StopWalkingBackward();

    void StartStrafingLeft();
    void StopStrafingLeft();

    void StartStrafingRight();
    void StopStrafingRight();

    void StartPlayerSee();

    void SetCameraTarget(GameObject * Target);

    void ToggleCamera();

    void SwitchCameraToFPS(bool bIsFPSCamera);

    bool IsUsingFPSCamera() const;

    void StopPlayerSee();

    const FPSCamera * GetCamera() const;

    const TPSCamera * GetTPSCamera() const;

    Vector3D GetLaunchPoint();
    

private:
    FPSCamera Camera;
    TPSCamera TPSCamera;

    bool bIsUsingTPSCamera = false;
    GameObject * CameraTarget = nullptr;

    Vector3D CameraOffset{0, 200, 0};
    Vector3D WeaponOffset{0, 10, 0};
    int TPSCameraDistanceBeetweenObject = 100;
    
    bool bIsGoingForward = false;
    bool bISGoingBackward = false;
    bool bIsStrafingLeft = false;
    bool bIsStrafingRight = false;

    bool bOpacityIsIncreasing = true;
    float opacity = 0;
    float Speed = 1000;
    float JumpForce = 2000;
    ofxAssimpModelLoader Weapon;
    ofImage WeaponTexture;



    const  int MaxAmmo = 10;
    int ammo = MaxAmmo;

    ofTrueTypeFont AmmoText;
    ofTrueTypeFont AmmoTextAmount;


};
