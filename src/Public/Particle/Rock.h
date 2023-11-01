#pragma once

#include "ofImage.h"
#include "Particle.h"
class Rock : public Particle
{
public:
    Rock(const Vector3D& Position, int Radius);
    void Setup() override;
    void Draw() const override;
    void Update(double f) override;
private:
};
