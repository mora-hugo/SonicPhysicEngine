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
    for(unsigned int i = 0; i < particles.size();)
    {
        for(unsigned int j = 0; j < particles.size(); j++)
        {
            if(i != j && i < particles.size() * 2 ) // If there is more than 2n collisions, then abandon the others
            {
                GameObject * p1 = particles[i];
                GameObject * p2 = particles[j];
                i++;
                if(p1->IsCollidingWith(*p2))
                {
                    CollisionData collisionData;
                    p1->CheckCollision(*p2,collisionData);
                    //Calculate the force
                    Vector3D movement = collisionData.CollisionNormal.Multiply(collisionData.PenetrationDepth).Multiply(p2->GetMass()/(p1->GetMass()+p2->GetMass()));
                    Force force(movement,1,p1,Constant);
                    particles[i]->AddForce(force);
                }
            }
        }
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

