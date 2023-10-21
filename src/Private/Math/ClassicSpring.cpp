#include "./../../Public/Math/ClassicSpring.h"
#include "../../Public/Particle/BlobParticle.h"

ClassicSpring::ClassicSpring()
{
}

ClassicSpring::ClassicSpring(GameObject* p1, GameObject* p2, double springConstant, double restLength, double damping)
    : particle1(p1), particle2(p2), springConstant(springConstant), restLength(restLength), damping(damping) {}

void ClassicSpring::applyForce() {
    Vector3D VectorNull = 0;
    Vector3D displacement = particle2->GetPosition() - particle1->GetPosition();
    double distance = displacement.Magnitude(); // Assuming you have a method for vector magnitude

    // Hooke's Law: F = -k * (x - L)
    double forceMagnitude = springConstant * (distance - restLength);

    // Calculate damping force
    Vector3D relativeVelocity = particle2->GetVelocity() - particle1->GetVelocity();
    double dampingForce = -damping * relativeVelocity.DotProduct(displacement.Divide(distance));

    // Calculate total force
    double totalForce = forceMagnitude + dampingForce;

    // Calculate force direction
    Vector3D forceDirection = displacement.Normalize(); // Assuming you have a method for vector normalization

    // Apply forces to the particles
    Vector3D force1 = forceDirection * totalForce;
    Vector3D force2 = VectorNull.Sub(force1);

    Force force1bis(force1,1,particle1,ForceType::Constant);
    Force force2bis(force1.Negate(),1,particle2,ForceType::Constant);

    particle1->AddForce(force1bis);
    particle2->AddForce(force2bis);
    
}