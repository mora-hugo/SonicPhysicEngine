#include "../../Public/Math/Vector3D.h"
#include "../../Public/Particle/Particle.h"
#include "time.h"

#include "ofGraphics.h"

Particle::Particle(const double& mass, const Vector3D& position, const Vector3D& velocity, const Vector3D& acceleration, const float radius) :
    position(position),velocity(velocity), acceleration(acceleration), mass(mass), radius(radius)
{
    ofSpherePrimitive::setRadius(radius);
}


void Particle::Draw() const
{
    ofSetColor(color);
    ofSpherePrimitive::draw();
}

void Particle::Update(clock_t f)
{
    SetFrameLength(f);
    std::cout << std::string(position) << std::endl;
    this->ApplyPhysics();
    setPosition(position);
}

void Particle::SetRadius(const float radius)
{
    ofSpherePrimitive::setRadius(radius);
}

void Particle::SetColor(const ofColor color)
{
    this->color = color;
}

void Particle::SetFrameLength(clock_t f)
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
    velocity = velocity + acceleration * FrameLength;
    //velocité instant k+1 = velocité instant k + longueur d'une frame * accélération
}

void Particle::UpdatePosition()
{
    position = position + velocity * FrameLength;
    //position instant k+1 = position instant k + longueur d'une frame * vélocité instant k+1
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
