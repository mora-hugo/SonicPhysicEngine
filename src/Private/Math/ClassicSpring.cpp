#include "./../../Public/Math/ClassicSpring.h"
#include "../../Public/Particle/BlobParticle.h"



ClassicSpring::ClassicSpring(GameObject* p1, GameObject* p2, double springConstant, double restLength, double damping)
    : Spring(p1,p2,springConstant,restLength,damping) {}

void ClassicSpring::applyForce() {
    Vector3D VectorNull = 0;
    Vector3D displacement = firstGameObject->GetPosition() - secondGameObject->GetPosition();
    double distance = displacement.Magnitude(); // Assuming you have a method for vector magnitude

    // Hooke's Law: F = -k * (x - L)
    double forceMagnitude = springConstant * (distance - restLength);

    // Calculate damping force
    Vector3D relativeVelocity = secondGameObject->GetVelocity() - firstGameObject->GetVelocity();
    double dampingForce = 0;
    if(relativeVelocity.MagnitudeSquared() != 0)
        dampingForce = -damping * relativeVelocity.DotProduct(displacement.Divide(distance));

    // Calculate total force
    double totalForce = forceMagnitude + dampingForce;

    // Calculate force direction
    Vector3D forceDirection = displacement.Normalize(); // Assuming you have a method for vector normalization

    // Apply forces to the particles
    Vector3D force1 = forceDirection * totalForce;
    Vector3D force2 = VectorNull.Sub(force1);

    Force force1bis(force1,1,firstGameObject,ForceType::Ressort);
    Force force2bis(force1.Negate(),1,secondGameObject,ForceType::Ressort);

    firstGameObject->AddForce(force1bis);
    secondGameObject->AddForce(force2bis);
    
}