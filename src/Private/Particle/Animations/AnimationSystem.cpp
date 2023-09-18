#include "../../../Public//Particle/Animations/AnimationSystem.h"

AnimationSystem::AnimationSystem(Particle* owner, const float Lifetime): Owner(owner),Lifetime(Lifetime),LifetimeRemaining(Lifetime)
{
    assert(owner != nullptr,"Owner particle must be defined");
}

AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::Draw() const
{
}


void AnimationSystem::StartAnimation()
{
    bIsPlaying = true;
}

void AnimationSystem::PauseAnimation()
{
    bIsInPause = true;
}

void AnimationSystem::AbortAnimation()
{
    bIsPlaying = false;
    bIsInPause = false;
    OnAnimationFinished();
}

void AnimationSystem::Update(clock_t f)
{
    LifetimeRemaining-=f;
    if(LifetimeRemaining<=0)
        OnAnimationFinished();
}

void AnimationSystem::OnAnimationFinished()
{
    bIsPlaying = false;
    bIsInPause = false;
    Owner->OnAnimationFinished();
};

bool AnimationSystem::IsInPause() const
{
    return bIsInPause;
}

bool AnimationSystem::IsFinished() const
{
    return !bIsPlaying;
}