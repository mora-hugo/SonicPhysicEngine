#pragma once
class GameObject;
class Spring
{
public:
    Spring() {};
    Spring(GameObject* p1, GameObject* p2, double springConstant, double restLength, double damping);
    virtual void applyForce() = 0;
    
protected:
    GameObject* firstGameObject;
    GameObject* secondGameObject;
    double springConstant;
    double restLength;
    double damping;
};
