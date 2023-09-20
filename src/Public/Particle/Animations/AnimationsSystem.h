#pragma once
#include <cassert>
#include <ctime>
#include "../../../Public/Particle/Particle.h"


class AnimationSystem
{
public:
    AnimationSystem(Particle * owner, const float Lifetime=0);
    
    virtual ~AnimationSystem();
    
    virtual void StartAnimation();
    
    virtual void PauseAnimation();

    virtual void AbortAnimation();

    virtual void Update(double f);

    virtual void Draw() const;



protected:
    virtual void OnAnimationFinished();
    
    Particle * Owner = nullptr;
    
    bool bIsPlaying = false;

    bool bIsInPause = false;

    const float Lifetime = 0;

    float LifetimeRemaining = 0;

public:
    // Getters and setters

    bool IsInPause() const;

    bool IsFinished() const;
    
};
