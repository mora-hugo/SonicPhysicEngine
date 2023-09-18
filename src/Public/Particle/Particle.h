#pragma once
#include "of3dPrimitives.h"
#include "../../Public/Math/Vector3D.h"

class Particle : protected ofSpherePrimitive
{
public:

    Particle(const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const Vector3D &acceleration = Vector3D::Zero(), const float radius = 10);

    virtual void Setup();
    
    virtual void Draw() const;

    virtual void Update(clock_t f);

    virtual void OnAnimationFinished();
    
protected:
    void ApplyPhysics();    

private:
    clock_t FrameLength = 0;
    Vector3D position = Vector3D::Zero();
    Vector3D velocity = Vector3D::Zero();
    Vector3D acceleration = Vector3D::Zero();
    double mass = 5;
    float radius = 30;
    ofColor color = ofColor::white;



public:
    // Getters and Setters

    void SetRadius(const float radius);

    void SetColor(const ofColor color);
    
    void SetFrameLength(clock_t f);

    clock_t getFrameLength();
    
    Vector3D GetPosition() const;

    Vector3D GetVelocity() const;

    Vector3D GetAcceleration() const;

    float GetRadius() const;

    double GetMass() const;

    double getReverseMass() const;

    void UpdateVelocity();

    void UpdatePosition();
};
