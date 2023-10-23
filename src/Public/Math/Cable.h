#ifndef CABLE_H
#define CABLE_H

#include "Spring.h"
#include "../../Public/GameObjects/GameObject.h"

class Cable : public Spring  {
public:
    Cable() {};
    Cable(GameObject* p1, GameObject* p2, double springConstant , double restLength,double damping, double maxSeparation);

    virtual void applyForce() override;

private:
    double maxSeparation;
};

#endif // CABLE_H
