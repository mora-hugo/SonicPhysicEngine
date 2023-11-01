#ifndef STALK_H
#define STALK_H

#include "Spring.h"
#include "../../Public/GameObjects/GameObject.h"

class Stalk : public Spring {
public:
    Stalk() {};
    Stalk(GameObject* p1, GameObject* p2, double springConstant, double restLength,double damping, double separationDistance);

    virtual void applyForce() override;

private:
    double separationDistance;
};

#endif // STALK_H


