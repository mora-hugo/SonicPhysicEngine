#pragma once

#include <vector>

#include "../../Public/Math/Vector3D.h"
#include "../../Public/Generator/ForceGenerator.h"
#include "../../Public/Generator/Force.h"
#include "../../Public/Config/Config.h"
#include "Structs/CollisionData.h"

class Force;

class GameObject
{
public:
    GameObject(const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const int radius = 10, const bool bIsUsingGravity = true);

    virtual void Setup();
    
    virtual void Draw();

    virtual void Update(double f);

    double GetMass() const;

    double GetReverseMass() const;
    
    bool IsSimulatePhysics() const;

    void AddForce(Force force);

    void GetImpulseFromCollision(GameObject * other, const Vector3D& collisionNormal, Vector3D & OutImpulseVector, bool bIsP1); 

    void cleanAccumForce();

    void modifyVelocity(double x, double y, double z);

    void SetSimulatePhysics(bool SimulatePhysics);
    
    Vector3D GetPosition() const;

    Vector3D GetVelocity() const;

    Vector3D GetAcceleration() const;
    
    float GetRadius() const;

    bool IsCollidingWith(const GameObject& other) const;

    void SetVelocity(Vector3D NewVelocity);

    void AddPosition(Vector3D Offset);

    void SetUsingGravity(bool bIsUsingGravity);

    bool GetUsingGravity() const;

    void AddImpulse(Vector3D ImpulseVector);

    //Tags
    void AddTag(const std::string& Tag);

    void RemoveTag(const std::string& Tag);

    bool HasTag(const std::string& Tag) const;

    void SetPosition(Vector3D NewPosition);

protected:
    

private:

    void ApplyPhysics(double DeltaTimes);

    virtual void UpdateVelocity(double Deltatimes);
    std::vector<Force> Forces;

    void UpdatePosition(double Deltatimes);

    Vector3D position = Vector3D::Zero();
    Vector3D velocity = Vector3D::Zero();
    Vector3D acceleration = Vector3D::Zero();
    double mass = 5;
    bool bSimulatePhysics = true;
    
    Vector3D AccumForce;
    int radius= 0;
    bool bUsingGravity = true;

    std::vector<std::string> Tags;
};
