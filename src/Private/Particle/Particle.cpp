#include "../../Public/Math/Vector3D.h"
#include "../../Public/Particle/Particle.h"
#include "time.h"

#include "ofGraphics.h"

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
    if(lifeTimeRemaining <= 0)
        SetIsFinished(true);
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
    //velocité instant k+1 = velocité instant k + longueur d'une frame (en secondes) * accélération
   // velocity = velocity + acceleration.Multiply(FrameLength);

    //coefficient de frottement
    //velocité instant k+1 = (coefficient damping)^longueur d'une frame  * velocité + longueur d'une frame (en secondes) * accélération
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
    
    /*
     * Ce qui était fait avant
     // Physics source : bob
    position = position + velocity;

    velocity = velocity.Add(Vector3D(0,mass/100,0));
    */
}
