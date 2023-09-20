#include "../../Public/Math/Vector3D.h"
#include "../../Public/Particle/Particle.h"
#include "time.h"

#include "ofGraphics.h"

Particle::Particle(const double& mass, const Vector3D& position, const Vector3D& velocity, const Vector3D& acceleration, const float radius) :
    position(position),velocity(velocity), acceleration(acceleration), mass(mass), radius(radius)
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
    this->ApplyPhysics();
    setPosition(position);
}

void Particle::OnAnimationFinished()
{
    
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

clock_t Particle::getFrameLength()
{
    return FrameLength;
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

double Particle::getReverseMass() const
{
    return 1/mass;
}

void Particle::UpdateVelocity()
{
    velocity = velocity + acceleration.Multiply(FrameLength*1000);
    //velocité instant k+1 = velocité instant k + longueur d'une frame (en ms) * accélération
}

void Particle::UpdatePosition()
{
    position = position + velocity.Multiply(FrameLength*1000);
    //position instant k+1 = position instant k + longueur d'une frame (en ms) * vélocité instant k+1
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
