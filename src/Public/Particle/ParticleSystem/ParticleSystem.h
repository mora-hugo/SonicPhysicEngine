#pragma once
#include "../Particle.h"

class ParticleSystem
{
public:
    ~ParticleSystem();

    void Setup();
    
    void Update(clock_t f);

    void Draw() const;
    
    Particle* AddParticle(Particle * particle);
    
private:
    std::vector<Particle*> particles;
};
