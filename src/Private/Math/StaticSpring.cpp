#include "../../Public/Math/StaticSpring.h"

StaticSpring::StaticSpring()
{
}

StaticSpring::StaticSpring(GameObject* p1, GameObject* p2, double springConstant, double restLength, double damping)
    : ClassicSpring(p1,p2, springConstant, restLength, damping) {}

void StaticSpring::applyForce()
{
    Vector3D displacement = particle2->GetPosition() - particle1->GetPosition();
    double distance = displacement.Magnitude();

    // Hooke's Law: F = -k * (x - L)
    double forceMagnitude = springConstant * (distance - restLength);

    // Calculate damping force
    Vector3D relativeVelocity = particle2->GetVelocity();
    double dampingForce = -damping * relativeVelocity.DotProduct(displacement.Divide(distance));

    // Calculate total force
    double totalForce = forceMagnitude + dampingForce;

    // Calculate force direction
    Vector3D forceDirection = displacement.Normalize();
    
    // Apply forces to the particles
    Vector3D force2 = forceDirection.Negate() * totalForce;
    Force force2bis(force2,1,particle2,ForceType::Constant);
    
    particle2->AddForce(force2bis);
}