#include "../../Public/GameObjects/GameObject.h"

#include <iostream>
#include <ostream>

#include "../../Public/Engine/GameWorld.h"

GameObject::GameObject(const double& mass, const Vector3D& position, const Vector3D& velocity,const int radius, const bool bIsUsingGravity) : radius(radius), position(position), velocity(velocity), mass(mass), bUsingGravity(bIsUsingGravity)
{
    
}

void GameObject::Setup()
{
}

void GameObject::Draw()
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
    
    //A la fin de la simulation on ajoute la force de friction avec l'air et la force de gravité qui s'appliqe à chaque pas de simulation
    Forces.push_back(Force(Vector3D(0.8,0.4,0),1,Friction));
    AccumForce = Vector3D().Zero();
    if(bUsingGravity)
        Forces.push_back(Force(Config::GRAVITY, 1, Constant));
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





void GameObject::SetVelocity(Vector3D NewVelocity)
{
    velocity = NewVelocity;
}

void GameObject::AddPosition(Vector3D Offset)
{
    position = position.Add(Offset);
}

void GameObject::SetUsingGravity(bool bIsUsingGravity)
{
    bUsingGravity = bIsUsingGravity;
}

bool GameObject::GetUsingGravity() const
{
    return bUsingGravity;
}

void GameObject::AddImpulse(Vector3D ImpulseVector)
{
    velocity = velocity + ImpulseVector.Multiply(GetReverseMass());
}

void GameObject::AddTag(const std::string& Tag)
{
    Tags.push_back(Tag);
}

void GameObject::RemoveTag(const std::string& Tag)
{
    //remove an occurrence of Tag in
    for(auto it = Tags.begin(); it != Tags.end(); ++it)
    {
        if(*it == Tag)
        {
            Tags.erase(it);
            break;
        }
    }

}

bool GameObject::HasTag(const std::string& Tag) const
{
    return std::find(Tags.begin(), Tags.end(), Tag) != Tags.end();
}

void GameObject::SetPosition(Vector3D NewPosition)
{
    position = NewPosition;
}

void GameObject::OnCollision(GameObject* other, CollisionData& Data)
{
}

void GameObject::SetCollision(bool bAllowCollision)
{
    bCanCollide = bAllowCollision;   
}

bool GameObject::CanCollide() const
{
    return bCanCollide;
}

bool GameObject::NeedToBeDestroyed() const
{
    return bNeedToBeDestroyed;
}

void GameObject::Destroy()
{
    bNeedToBeDestroyed = true;
}


void GameObject::ApplyPhysics(double DeltaTimes)
{
    UpdateVelocity(DeltaTimes);
    UpdatePosition(DeltaTimes);
    cleanAccumForce();
}

void GameObject::UpdateVelocity(double Deltatimes)
{


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
            //On va set la velocity pour faire des déplacement plus "jeux vidéos" / plus maniable
            velocity.SetX(Forces[i].movement.GetX());
            break;
        case ImpulseJump:
            //On va set la velocity pour faire des déplacement plus "jeux vidéos" / plus maniable
            velocity.SetY(Forces[i].movement.GetY());
            break;
        case Friction:
            //Ne prend en compte que le frottement de l'air à modifier quand on aura les collisions
            //AccumForce = AccumForce + velocity.Negate().ComponentProduct(velocity.Normalize() * Forces[i].movement.GetX() + velocity.Normalize().ComponentProduct(velocity.Normalize())* Forces[i].movement.GetY());
            break;
        case Ressort:
            AccumForce = AccumForce + Forces[i].movement;
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
