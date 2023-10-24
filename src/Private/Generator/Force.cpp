#include "../../Public/Generator/Force.h"
#include "../../Public/GameObjects/GameObject.h"

Force::Force(const Vector3D& movement, double lifetime, ForceType type)
        : movement(movement),
          lifetime(lifetime),
          type(type)
{
}