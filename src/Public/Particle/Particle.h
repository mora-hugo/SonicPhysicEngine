#pragma once
#include "of3dPrimitives.h"
#include "ofSoundPlayer.h"
#include "../../Public/Math/Vector3D.h"
#include "Public/Generator/ForceGenerator.h"
#include "Public/Generator/Force.h"

class Particle :public ForceGenerator, protected ofSpherePrimitive
{
public:

    Particle(const double &mass = 1, const float lifetime = 10, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const Vector3D &acceleration = Vector3D::Zero(), const float radius = 10);

    virtual void Setup();
    
    virtual void Draw() const;

    virtual void Update(double f);

    virtual void OnAnimationFinished();

    ofSoundPlayer ExplosionSound;
    
    std::vector<Force> Forces;
    
protected:
    void ApplyPhysics();    

private:
    double FrameLength = 0;
    Vector3D position = Vector3D::Zero();
    Vector3D velocity = Vector3D::Zero();
    Vector3D acceleration = Vector3D::Zero();
    double mass = 5;
    float radius = 30;
    ofColor color = ofColor::white;
    bool bIsFinished = false;
    float lifeTime = 0;
    float lifeTimeRemaining = 0;

    bool bSimulatePhysics = true;


public:
    // Getters and Setters

    void SetIsFinished(const bool isFinished);
    
    void SetRadius(const float radius);

    void SetColor(const ofColor color);
    
    void SetFrameLength(double f);

    double getFrameLength();

    float GetLifetime() const;

    float GetLifetimeRemaining() const;
    
    bool GetIsFinished();

    void SetSimulatePhysics(bool SimulatePhysics);
    
    Vector3D GetPosition() const;

    Vector3D GetVelocity() const;

    Vector3D GetAcceleration() const;


    float GetRadius() const;

    double GetMass() const;

    double GetReverseMass() const;

    void UpdateVelocity();

    void UpdatePosition();

    bool IsSumulatePhysics() const;

    Force AccumForce();

    void AddForce(Force force);

    void cleanAccumForce();

    void UpdateForce(Force force) override;
    
};
