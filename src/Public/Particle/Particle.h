#pragma once
#include "of3dPrimitives.h"

class Particle : protected ofSpherePrimitive
{
public:

    Particle(const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const Vector3D &acceleration = Vector3D::Zero(), const float radius = 10);

    void Draw() const;

    void Update(clock_t f);

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
    
protected:
    void ApplyPhysics();    

private:
    clock_t FrameLength;
    Vector3D position;
    Vector3D velocity;
    Vector3D acceleration;
    double mass = 5;
    float radius = 30;
    ofColor color = ofColor::white;
    
};
