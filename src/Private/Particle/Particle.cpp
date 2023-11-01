#include "../../Public/Math/Vector3D.h"
#include "../../Public/Particle/Particle.h"
#include "time.h"

#include "ofGraphics.h"
#include "../../Public/Generator/Force.h"

Particle::Particle(const double& _mass, const float lifetime, const Vector3D& _position, const Vector3D& _velocity, const float radius, const bool bIsUsingGravity) :
   GameObject(_mass,_position,_velocity,radius,bIsUsingGravity) , lifeTime(lifetime), lifeTimeRemaining(lifeTime)
{
    ofSpherePrimitive::setRadius(radius);
}

void Particle::Setup()
{
    GameObject::Setup();
}

void Particle::Draw()
{
    GameObject::Draw();
    ofSetColor(color);
    ofSpherePrimitive::draw();
}

void Particle::Update(double f)
{
    GameObject::Update(f);
    setPosition(GetPosition());
}


void Particle::OnAnimationFinished()
{
    //DeleteObject(this);
}

void Particle::SetFaces(int nb)
{
    this->setResolution(nb);
}

void Particle::SetIsFinished(const bool isFinished)
{
    bIsFinished = isFinished;
}

bool Particle::GetIsFinished()
{
    return bIsFinished;
}


void Particle::SetRadius(const float radius)
{
    ofSpherePrimitive::setRadius(radius);
}

void Particle::SetColor(const ofColor color)
{
    this->color = color;
    
}

void Particle::SetFrameLength(double f)
{
    FrameLength = f;
}

double Particle::getFrameLength()
{
    return FrameLength;
}

float Particle::GetLifetime() const
{
    return lifeTime;
}

float Particle::GetLifetimeRemaining() const
{
    return lifeTimeRemaining;
}

void Particle::SetDamping(double damping) {
    this->damping = damping;
}
