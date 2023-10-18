#include "../../Public/Math/Vector3D.h"
#include "../../Public/Particle/Particle.h"
#include "time.h"

#include "ofGraphics.h"
#include "../../Public/Generator/Force.h"

Particle::Particle(const double& mass, const float lifetime, const Vector3D& position, const Vector3D& velocity, const Vector3D& acceleration, const float radius) :
    position(position),velocity(velocity), acceleration(acceleration), mass(mass), radius(radius), lifeTime(lifetime), lifeTimeRemaining(lifeTime)
{
    ofSpherePrimitive::setRadius(radius);
}

void Particle::Setup()
{
    
}


void Particle::Draw() const
{
    ofSetColor(color);
    ofSpherePrimitive::draw();
}

void Particle::Update(double f)
{
    SetFrameLength(f);
    lifeTimeRemaining-=f;
    /*if(lifeTimeRemaining <= 0)
        SetIsFinished(true);*/
    if(bSimulatePhysics)
        this->ApplyPhysics();
    setPosition(position);
}

void Particle::OnAnimationFinished()
{
    //DeleteObject(this);
}

void Particle::SetIsFinished(const bool isFinished)
{
    bIsFinished = isFinished;
}

bool Particle::GetIsFinished()
{
    return bIsFinished;
}

void Particle::SetSimulatePhysics(bool SimulatePhysics)
{
    bSimulatePhysics = SimulatePhysics;
}

bool Particle::IsSumulatePhysics() const
{
    return bSimulatePhysics;
}

Force Particle::AccumForce()
{
    Force res = Force(NULL, 60, this, Constant) ; //somme des forces
    
    for (int i=0 ; i < Forces.size() ; ++i)
    {
        if (Forces[i].lifetime <= 0)
        {
           Forces.erase(Forces.begin()+i);
        } else
        {
            res.movement = res.movement + Forces[i].movement;
            acceleration = Forces[i].movement * GetReverseMass();
            Forces[i].lifetime = Forces[i].lifetime - getFrameLength();
        }
    }
    return res;
}

void Particle::AddForce(Force force)
{
    Forces.push_back(force);
}

void Particle::cleanAccumForce()
{
    Forces.clear();
}

void Particle::UpdateForce(Force force)
{
    switch (type)
    {
    case Input:
        break;
    case Environnement:
        break;
    case Constant:
        break;
    case Friction:
        break;
    case Ressort:
        break;
    }
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


Vector3D Particle::GetPosition() const
{
    return this->position;
}

Vector3D Particle::GetVelocity() const
{
    return this->velocity;
}

Vector3D Particle::GetAcceleration() const
{
    return this->acceleration;
}

float Particle::GetRadius() const
{
    return this->radius;
}

double Particle::GetMass() const
{
    return this->mass;
}

double Particle::GetReverseMass() const
{
    return 1/mass;
}

void Particle::UpdateVelocity()
{
    //coefficient de frottement
    //velocité instant k+1 = (coefficient damping)^longueur d'une frame  * velocité + longueur d'une frame (en secondes) * accélération

    Force force = AccumForce();
    velocity = velocity.Multiply(pow(0.97, FrameLength)) + acceleration.Multiply(FrameLength);
}

void Particle::UpdatePosition()
{
    //position instant k+1 = position instant k + longueur d'une frame (en secondes) * vélocité instant k+1
    position = position + velocity.Multiply(FrameLength);
}

void Particle::ApplyPhysics()
{
    UpdateVelocity();
    UpdatePosition();
}
