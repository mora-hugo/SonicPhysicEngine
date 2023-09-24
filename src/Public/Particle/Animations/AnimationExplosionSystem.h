#pragma once
#include "AnimationSystem.h"
#include "../ParticleSystem/ParticleSystem.h"

class AnimationExplosionSystem : public AnimationSystem
{
public:
    AnimationExplosionSystem(Particle* owner, float lifetime = 0, const int SparksNumber = 20) : AnimationSystem(owner, lifetime), SparksNumber(SparksNumber)
    {
    }

    void StartAnimation() override;
    
    void PauseAnimation() override;

    void AbortAnimation() override;

    void Draw() const override;
    
    void Update(double f) override;

    ofColor GetRandomColor() const;
    
protected:
    void OnAnimationFinished() override;

    const int SparksNumber = 0;
    ParticleSystem Sparks;

    
public:
    
};
