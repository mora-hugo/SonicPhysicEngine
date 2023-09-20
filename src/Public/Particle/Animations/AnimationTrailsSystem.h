#pragma once
#include "AnimationSystem.h"
#include "../ParticleSystem/ParticleSystem.h"

class AnimationTrailsSystem : public AnimationSystem
{
public:
    AnimationTrailsSystem(Particle* owner, float lifetime = 0) : AnimationSystem(owner, lifetime)
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

    ParticleSystem Trails;

    
public:
    
};
