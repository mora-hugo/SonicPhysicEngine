#pragma once

#include "ofImage.h"
#include "ofPixels.h"
#include "Particle.h"
class Rock : public Particle
{
public:
    Rock(ofImage * image, const Vector3D& Position, int Radius);
    void Setup() override;
    void Draw() override;
    void Update(double f) override;
private:
    ofImage* texture;
};
