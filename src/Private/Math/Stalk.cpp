#include "Stalk.h"

#include "Vector3D.h"

Stalk::Stalk(GameObject* p1, GameObject* p2, double springConstant, double restLength,double damping, double separationDistance)
    : Spring(p1, p2, springConstant, restLength, damping), separationDistance(separationDistance) {}

void Stalk::applyForce() {
    Vector3D displacement = firstGameObject->GetPosition() - secondGameObject->GetPosition();
    double distance = displacement.Magnitude();

    // Calculate the required displacement to maintain the separation distance
    double requiredDisplacement = separationDistance - distance;
    Vector3D correction = displacement.Normalize() * requiredDisplacement;

    // Apply the correction to both particles
    Vector3D correction1 = correction * 0.5;
    Vector3D correction2 = correction1.Negate();

    firstGameObject->AddPosition(correction1);
    secondGameObject->AddPosition(correction2);
}
