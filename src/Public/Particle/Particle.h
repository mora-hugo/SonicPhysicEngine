#pragma once
#include "of3dPrimitives.h"
#include "ofSoundPlayer.h"
#include "../../public/GameObjects/GameObject.h"
#include "../../Public/Math/Vector3D.h"
#include "../../Public/Generator/ForceGenerator.h"
#include "../../Public/Generator/Force.h"

class Particle : public ForceGenerator, protected ofSpherePrimitive, public GameObject
{
public:

    Particle(const double &mass = 1, const float lifetime = 10, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const float radius = 10, const bool bIsUsingGravity = true);

    virtual void Setup() override;
    
    virtual void Draw() const override;

    virtual void Update(double f) override ;

    virtual void OnAnimationFinished();

    ofSoundPlayer ExplosionSound;
    
    std::vector<Force> Forces;

    Vector3D AccumForce;
    
    double damping;

protected:

private:
    double FrameLength = 0;
  
    ofColor color = ofColor::white;
    bool bIsFinished = false;
    float lifeTime = 0;
    float lifeTimeRemaining = 0;

public:
    // Getters and Setters

    void SetFaces(int nb);
    void SetIsFinished(const bool isFinished);
    
    void SetRadius(const float radius);

    void SetColor(const ofColor color);
    
    void SetFrameLength(double f);

    double getFrameLength();

    float GetLifetime() const;

    float GetLifetimeRemaining() const;
    
    bool GetIsFinished();



    void SetDamping(double damping);


};
