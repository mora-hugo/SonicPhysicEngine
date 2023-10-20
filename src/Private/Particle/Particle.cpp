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

void Particle::AddForce(Force force)
{
    Forces.push_back(force);
}

void Particle::cleanAccumForce()
{
    for (int i=0 ; i < Forces.size() ; ++i)
    {
        if (Forces[i].lifetime <=0)
        {
            Forces.erase(Forces.begin()+i);
        }
    }
    Forces.push_back(Force(Vector3D(0.4,0.4,0),1,this,Friction));
    AccumForce = Vector3D();
    Forces.push_back(Force(Vector3D(0,9.8), 1 , this, Constant));
}

void Particle::setVelocity(double x, double y, double z)
{
    velocity = velocity.ComponentProduct(Vector3D(x,y,z));
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
    //coefficient de friction cinétique
    Force friction = Force(Vector3D(1,1,1),1,this,Friction);
    
    for (int i=0 ; i < Forces.size() ; ++i)
    {
        //AccumForce = AccumForce + Forces[i].movement;
        Forces[i].lifetime = Forces[i].lifetime - 1;
        //std::cout << Forces[i].lifetime << std::endl;

        switch (Forces[i].type)
        {
        case Constant:
            AccumForce = AccumForce + Forces[i].movement;
            break;
        case Input :
            AccumForce = AccumForce + Forces[i].movement;
            break;
        case InputJump:
            AccumForce = AccumForce + Forces[i].movement;
            break;
        case Friction:
            //Ne prend en compte que le frottement de l'air à modifier quand on aura les collisions
            //AccumForce = AccumForce + velocity.Negate().ComponentProduct(velocity.Normalize() * Forces[i].movement.GetX() + velocity.Normalize().ComponentProduct(velocity.Normalize())* Forces[i].movement.GetY());
            break;
        case Ressort:
            break;
        case Environnement:
            break;
        }
    }
    acceleration = AccumForce * GetReverseMass();
    
    //velocité instant k+1 = (coefficient damping)^longueur d'une frame  * velocité + longueur d'une frame (en secondes) * accélération
    velocity = velocity + acceleration.Multiply(FrameLength);
    std::cout << std::string(velocity) << std::endl;
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
    cleanAccumForce();
}
