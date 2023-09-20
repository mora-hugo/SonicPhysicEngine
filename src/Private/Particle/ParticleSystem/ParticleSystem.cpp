#include "../../../Public/Particle/ParticleSystem/ParticleSystem.h"


ParticleSystem::~ParticleSystem()
{
    for(unsigned int i = 0; i < particles.size(); i++)
    {
        // Remove the particle if it is finished
        delete particles[i];
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
    for(unsigned int i = 0; i < particles.size(); i++)
    {
        if(particles[i]->GetIsFinished())
        {
            /*
            delete particles[i];
            particles.erase(particles.begin() + i);
            */
        }
        particles[i]->Update(f);
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

