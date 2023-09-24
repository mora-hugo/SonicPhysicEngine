#include "../../../Public/Particle/Animations/AnimationExplosionSystem.h"

#include "../../../Public/Particle/ParticleSparksTrails.h"

void AnimationExplosionSystem::StartAnimation()
{
    AnimationSystem::StartAnimation();
    
    for(int i = 0; i < SparksNumber; i++)
    {
        double rad = i*2*PI/SparksNumber;
        double x = Owner->GetRadius()*cos(rad);
        double y = Owner->GetRadius()*sin(rad);
        Particle * p = Sparks.AddParticle(new ParticleSparksTrails(5, Lifetime,Owner->GetPosition(),Vector3D(x,y).Multiply(25),Owner->GetAcceleration().Multiply(5),Owner->GetRadius()*1.115));
        p->SetColor(GetRandomColor());

        
    }
    Sparks.Setup();
}

void AnimationExplosionSystem::PauseAnimation()
{
    AnimationSystem::PauseAnimation();
    
}

void AnimationExplosionSystem::AbortAnimation()
{
    AnimationSystem::AbortAnimation();
    
}

void AnimationExplosionSystem::Draw() const
{
    AnimationSystem::Draw();
    if(!bIsPlaying) return;
    Sparks.Draw();
    std::cout << "Class AnimationExplosionSystem : Draw" <<  std::endl;
}

void AnimationExplosionSystem::Update(double f)
{
    AnimationSystem::Update(f);
    if(!bIsPlaying || bIsInPause) return;
    Sparks.Update(f);
    std::cout << "Class AnimationExplosionSystem : Update" <<  std::endl;
    
}

ofColor AnimationExplosionSystem::GetRandomColor() const
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

void AnimationExplosionSystem::OnAnimationFinished()
{
    AnimationSystem::OnAnimationFinished();
    Owner->OnAnimationFinished();
}
