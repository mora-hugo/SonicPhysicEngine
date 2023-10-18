#include "../../Public/Generator/ForceGenerator.h"

#include "../../Public/Generator/Force.h"
#include "Particle.h"

void ForceGenerator::UpdateForce(Force force, Particle particle)
{
    particle.AddForce(force);
}
