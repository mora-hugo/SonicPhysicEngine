#include "../../../Public/Particle/ParticleSystem/ParticleSystem.h"


ParticleSystem::~ParticleSystem()
{
    for(unsigned int i = 0; i < particles.size();)
    {
        delete particles[i];
        particles[i] = nullptr;
        // Remove the element from the vector and don't increment i
        particles.erase(particles.begin() + i);
    }
}

void ParticleSystem::Setup()
{
    for(Particle * particle: particles)
    {
        particle->Setup();
    }
}

void ParticleSystem::Update(double f)
{
    int i = 0;
    
    if(particles[i]->GetIsFinished())
    {
        delete particles[i];
        particles[i] = nullptr;
        // Remove the element from the vector and don't increment i
        particles.erase(particles.begin() + i);
    }
    else
    {
        particles[i]->Update(f);
        i++;
    }

    
}

void ParticleSystem::Draw() const
{
    for(const Particle * particle: particles)
    {
        particle->Draw();
    }
}

Particle* ParticleSystem::AddParticle(Particle* particle)
{
    particles.push_back(particle);
    return particle;
}

