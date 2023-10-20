#pragma once

#include <vector>

#include "../../Public/Math/Vector3D.h"
#include "../../Public/Generator/ForceGenerator.h"
#include "../../Public/Generator/Force.h"

class Force;

class GameObject
{
public:
    GameObject(const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const Vector3D &acceleration = Vector3D::Zero());

    virtual void Setup();
    
    virtual void Draw() const;

    virtual void Update(double f);

    double GetMass() const;

    double GetReverseMass() const;
    
    bool IsSimulatePhysics() const;

    void AddForce(Force force);

    void cleanAccumForce();

    void setVelocity(double x, double y, double z);

    void SetSimulatePhysics(bool SimulatePhysics);
    
    Vector3D GetPosition() const;

    Vector3D GetVelocity() const;

    Vector3D GetAcceleration() const;
    
private:
    void ApplyPhysics(double DeltaTimes);

    void UpdateVelocity(double Deltatimes);

    void UpdatePosition(double Deltatimes);

    
    Vector3D position = Vector3D::Zero();
    Vector3D velocity = Vector3D::Zero();
    Vector3D acceleration = Vector3D::Zero();
    double mass = 5;
    bool bSimulatePhysics = true;
    std::vector<Force> Forces;
    Vector3D AccumForce;
};
