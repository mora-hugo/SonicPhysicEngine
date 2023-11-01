#pragma once
#include "FPSCamera.h"
#include "ofCamera.h"
#include "../Particle/BlobParticle.h"

class Player : public GameObject
{

public:
    
    Player(ofApp * Context, const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), int SphereRadius = 10);
    void OnRotate(const Vector3D& DeltaRot);
    void Setup() override;
    void Draw() const override;
    void Update(double f) override;

    void Jump();

    void StartWalkingForward();
    void StopWalkingForward();
    

private:
    FPSCamera * Camera;

    Vector3D CameraOffset{0, 80, 0};

    bool bIsGoingForward = false;

    float Speed = 1000;
    float JumpForce = 2000;
};
