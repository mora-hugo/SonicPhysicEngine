#include "../../Public/Generator/Force.h"

Force::Force(const Vector3D& movement, double lifetime, Particle* particle, ForceType type)
        : movement(movement),
          lifetime(lifetime),
          particle(particle),
          type(type)
{
}