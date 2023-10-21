#include "../../Public/Math/Vector3D.h"
#include "../../Public/Particle/ParticleSparksTrails.h"
#include "time.h"

#include "ofGraphics.h"

ParticleSparksTrails::ParticleSparksTrails(const double& mass, const float lifetime, const Vector3D& position, const Vector3D& velocity, const Vector3D& acceleration, const float radius) :
Particle(mass,lifetime, position,velocity,radius), ATS(this,lifetime)
{
    ofSpherePrimitive::setRadius(radius);

}

void ParticleSparksTrails::Setup()
{
    ATS.StartAnimation();
}


void ParticleSparksTrails::Draw() const
{
    Particle::Draw();
    ATS.Draw();
    
}

void ParticleSparksTrails::Update(double f)
{
    Particle::Update(f);
    ATS.Update(f);
}

void ParticleSparksTrails::OnAnimationFinished()
{
    // The particle will be garbage collected with the particle system
    SetIsFinished(true); 
}

