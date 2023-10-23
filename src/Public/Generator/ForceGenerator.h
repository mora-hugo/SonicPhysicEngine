#pragma once

class Force;
class Particle;

enum ForceType
{
    Constant,
    Input,
    ImpulseJump,
    Friction,
    Ressort,
    Environnement
};

class ForceGenerator
{
public:
    ForceType type = Input;
    void UpdateForce(Force force, Particle particle);
};
