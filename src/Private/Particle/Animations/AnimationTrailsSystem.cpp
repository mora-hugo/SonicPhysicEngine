#include "../../../Public/Particle/Animations/AnimationTrailsSystem.h"

void AnimationTrailsSystem::StartAnimation()
{
    AnimationSystem::StartAnimation();
    
}

void AnimationTrailsSystem::PauseAnimation()
{
    AnimationSystem::PauseAnimation();
    
}

void AnimationTrailsSystem::AbortAnimation()
{
    AnimationSystem::AbortAnimation();
    
}

void AnimationTrailsSystem::Draw() const
{
    if(!bIsPlaying) return;
    Trails.Draw();
}

void AnimationTrailsSystem::Update(double f)
{
    if(!bIsPlaying || bIsInPause) return;
    Particle * p = Trails.AddParticle( new Particle(5,Owner->GetPosition(),Owner->GetVelocity().Negate().Multiply(0.2).Multiply(ofRandom(0.1,1.5)),Vector3D(0,0.00098),Owner->GetRadius()/1.75f*ofRandom(0.5,1.2)));
    p->SetColor(GetRandomColor());
    Trails.Update(f);
    
}

ofColor AnimationTrailsSystem::GetRandomColor() const
{
    const unsigned int Color = ofRandom(1,5);
    switch (Color)
    {
    case 1:
        return ofColor::orange;
    case 2:
        return ofColor::orangeRed;
    case 3:
        return ofColor::darkOrange;
    case 4:
        return ofColor::yellow;
    case 5:
        return ofColor::darkRed;
    default:
        break;
    }
    return ofColor::orange;

}

void AnimationTrailsSystem::OnAnimationFinished()
{
    AnimationSystem::OnAnimationFinished();
    
}
