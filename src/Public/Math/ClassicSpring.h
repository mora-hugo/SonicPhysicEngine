#ifndef SPRING_H
#define SPRING_H

#include "../Particle/BlobParticle.h"

class ClassicSpring {
public:
    ClassicSpring();
    ClassicSpring(BlobParticle* p1, BlobParticle* p2, double springConstant, double restLength, double damping);
    void applyForce();
    
protected:
    Particle* particle1;
    Particle* particle2;
    double springConstant;
    double restLength;
    double damping;
};

#endif // SPRING_H
