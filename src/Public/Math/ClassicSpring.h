#ifndef SPRING_H
#define SPRING_H

#include "../Particle/BlobParticle.h"

class ClassicSpring {
public:
    ClassicSpring();
    ClassicSpring(GameObject* p1, GameObject* p2, double springConstant, double restLength, double damping);
    virtual void applyForce();
    
protected:
    GameObject* particle1;
    GameObject* particle2;
    double springConstant;
    double restLength;
    double damping;
};

#endif // SPRING_H
