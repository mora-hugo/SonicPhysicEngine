#pragma once

class Force;
class Particle;

enum ForceType
{
    Constant,
    Input,
    Friction,
    Ressort,
    Environnement
};

class ForceGenerator
{
public:
    ForceType type = Input;
    virtual void UpdateForce(Force force)=0;
};
