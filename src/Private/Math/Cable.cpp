#include "../../Public/Math/Cable.h"

#include "../../Public/Math/Vector3D.h"

Cable::Cable(GameObject* p1, GameObject* p2, double springConstant, double restLength,double damping, double maxSeparation)
    : Spring(p1, p2, springConstant, restLength, damping), maxSeparation(maxSeparation) {}

void Cable::applyForce() {
    Vector3D displacement =  firstGameObject->GetPosition() - secondGameObject->GetPosition();
    double distance = displacement.Magnitude();

    // Check if the particles exceed the maximum separation
    if (distance > maxSeparation) {
        // Calculate the spring force to bring them back within the maximum separation
        double forceMagnitude = springConstant * (distance - maxSeparation);
        Vector3D forceDirection = displacement.Normalize();
        Vector3D force1 = forceDirection * forceMagnitude;

        // Apply the forces to the particles
        firstGameObject->AddImpulse(force1.Negate());
        secondGameObject->AddImpulse(force1);
    }
}
