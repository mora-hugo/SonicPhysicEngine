#ifndef SPRING_H
#define SPRING_H

#include "../Particle/BlobParticle.h"
#include "Spring.h"

class ClassicSpring : public Spring{
public:
    ClassicSpring() {};
    ClassicSpring(GameObject* p1, GameObject* p2, double springConstant, double restLength, double damping);
    void applyForce() override;
};

#endif // SPRING_H
