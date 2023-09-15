#pragma once
#include "of3dPrimitives.h"

class Particle : protected ofSpherePrimitive
{
public:

    Particle(const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const Vector3D &acceleration = Vector3D::Zero(), const float radius = 10);

    void Draw() const;

    void Update();

    void SetRadius(const float radius);

    void SetColor(const ofColor color);
    

    Vector3D GetPosition() const;

    Vector3D GetVelocity() const;

    Vector3D GetAcceleration() const;

    float GetRadius() const;

    double GetMass() const;
    
protected:
    void ApplyPhysics();

    

private:

    Vector3D position;
    Vector3D velocity;
    Vector3D acceleration;
    double mass = 0;
    float radius = 0;
    ofColor color = ofColor::white;
    
};
