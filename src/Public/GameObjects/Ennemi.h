#pragma once
#include "ofxAssimpModelLoader.h"
#include "RigidBody.h"

class Ennemi : public GameObject
{
public:
    Ennemi(const std::string &filepath,const Vector3D &position, const Vector3D& scale = Vector3D(1, 1, 1));
    ~Ennemi();

    void SetTarget(const Vector3D& target);
    void FollowTargetOn(bool bFollow);

    virtual void Update(double f) override;
    void Draw() override;

    void AddRotation(const EulerAngle& rotation);

    void SetTargetGameObject(GameObject * target);

    void SetRotation(const EulerAngle& rotation);

    void ProcessIA();
    
    virtual void OnCollision(GameObject* other, CollisionData& Data) override;

private:
    bool bIsFollowingTarget = false;
    Vector3D Scale = Vector3D(1,1,1);
    ofxAssimpModelLoader modelLoaded;
    Vector3D CurrentTarget;
    EulerAngle CurrentRotation;
    Quaternion quat = Quaternion::identity();
    GameObject * TargetGameObject = nullptr;
    Vector3D ModelOffset {0,50,0};
    float Speed = 5;

    bool bIsDead = false;
    float Life = 100;
    const float Maxlife = 100;
    
};


