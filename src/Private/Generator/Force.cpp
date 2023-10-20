#include "../../Public/Generator/Force.h"
#include "../../Public/GameObjects/GameObject.h"

Force::Force(const Vector3D& movement, double lifetime, GameObject* particle, ForceType type)
        : movement(movement),
          lifetime(lifetime),
          particle(particle),
          type(type)
{
}