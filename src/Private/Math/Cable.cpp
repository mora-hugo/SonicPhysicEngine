#include "Cable.h"

#include "Vector3D.h"

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

        Force force1bis(force1.Negate(),1,firstGameObject,ForceType::Ressort);
        Force force2bis(force1,1,secondGameObject,ForceType::Ressort);

        // Apply the forces to the particles
        firstGameObject->AddForce(force1bis);
        secondGameObject->AddForce(force2bis);
    }
}
