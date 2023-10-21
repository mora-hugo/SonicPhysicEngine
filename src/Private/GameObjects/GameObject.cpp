#include "../../Public/GameObjects/GameObject.h"

#include <iostream>
#include <ostream>

GameObject::GameObject(const double& mass, const Vector3D& position, const Vector3D& velocity,
                       const Vector3D& acceleration, const int radius) : radius(radius), position(position), velocity(velocity), acceleration(acceleration), mass(mass)
{
}

void GameObject::Setup()
{
}

void GameObject::Draw() const
{
}

void GameObject::Update(double f)
{
    if(bSimulatePhysics)
        this->ApplyPhysics(f);
}

double GameObject::GetMass() const
{
    return mass;
}

double GameObject::GetReverseMass() const
{
    return 1/mass;
}

bool GameObject::IsSimulatePhysics() const
{
    return bSimulatePhysics;
}

void GameObject::AddForce(Force force)
{
    Forces.push_back(force);
}

void GameObject::GetImpulseFromCollision(GameObject * other, const Vector3D& collisionNormal, Vector3D & OutImpulseVector, bool bIsP1)
{
    const float restitutionCoef = 0.7;
    
    Vector3D relativeVelocity;
    if(bIsP1)
        relativeVelocity = velocity.Sub(other->GetVelocity());
    else
        relativeVelocity = other->GetVelocity().Sub(velocity);
    
    const double Numerator = ((restitutionCoef + 1) * (relativeVelocity.DotProduct(collisionNormal)));
    const double Denominator = (GetReverseMass() + other->GetReverseMass());
    const double K = Numerator / Denominator;
    if(bIsP1)
        OutImpulseVector =  GetVelocity().Sub((collisionNormal.Multiply(K))*GetReverseMass());
    else
        OutImpulseVector =  GetVelocity().Add((collisionNormal.Multiply(K))*GetReverseMass());
}

void GameObject::cleanAccumForce()
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

void GameObject::modifyVelocity(double x, double y, double z)
{
    velocity = velocity.ComponentProduct(Vector3D(x,y,z));
}


void GameObject::SetSimulatePhysics(bool SimulatePhysics)
{
}

Vector3D GameObject::GetPosition() const
{
    return position;    
}

Vector3D GameObject::GetVelocity() const
{
    return velocity;
}

Vector3D GameObject::GetAcceleration() const
{
    return acceleration;
}

float GameObject::GetRadius() const
{
    return radius;
}

bool GameObject::IsCollidingWith(const GameObject& other) const
{
    const float radius = GetRadius() + other.GetRadius();
    const float distance = GetPosition().Distance(other.GetPosition());
    return (distance <= radius);
}

void GameObject::CheckCollision(const GameObject& other, CollisionData& collisionData) const
{

}

void GameObject::SetCollisionWasChecked(bool CollisionWasChecked)
{
    this->bCollisionWasChecked = CollisionWasChecked;
    
}

bool GameObject::GetCollisionWasChecked() const
{
    return bCollisionWasChecked;
}

void GameObject::SetVelocity(Vector3D NewVelocity)
{
    velocity = NewVelocity;
}

void GameObject::AddPosition(Vector3D Offset)
{
    position = position.Add(Offset);
}


void GameObject::ApplyPhysics(double DeltaTimes)
{
    UpdateVelocity(DeltaTimes);
    UpdatePosition(DeltaTimes);
    cleanAccumForce();
}

void GameObject::UpdateVelocity(double Deltatimes)
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
    velocity = velocity + acceleration.Multiply(Deltatimes);
}

void GameObject::UpdatePosition(double Deltatimes)
{
    position = position + velocity.Multiply(Deltatimes);
}
