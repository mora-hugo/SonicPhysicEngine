#include "../../Public/Generator/ForceGenerator.h"

#include "../../Public/Generator/Force.h"
#include "../../Public/Particle/Particle.h"

void ForceGenerator::UpdateForce(Force force, Particle particle)
{
    particle.AddForce(force);
}
