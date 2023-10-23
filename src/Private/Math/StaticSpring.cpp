#include "../../Public/Math/StaticSpring.h"



StaticSpring::StaticSpring(GameObject* p1, GameObject* p2, double springConstant, double restLength, double damping)
    : Spring(p1,p2, springConstant, restLength, damping) {}

void StaticSpring::applyForce()
{
    Vector3D displacement = secondGameObject->GetPosition() - firstGameObject->GetPosition();
    double distance = displacement.Magnitude();

    // Hooke's Law: F = -k * (x - L)
    double forceMagnitude = springConstant * (distance - restLength);

    // Calculate damping force
    Vector3D relativeVelocity = secondGameObject->GetVelocity();
    double dampingForce = -damping * relativeVelocity.DotProduct(displacement.Divide(distance));

    // Calculate total force
    double totalForce = forceMagnitude + dampingForce;

    // Calculate force direction
    Vector3D forceDirection = displacement.Normalize();
    
    // Apply forces to the particles
    Vector3D force2 = forceDirection.Negate() * totalForce;
    Force force2bis(force2,1,secondGameObject,ForceType::Ressort);
    
    secondGameObject->AddForce(force2bis);
}