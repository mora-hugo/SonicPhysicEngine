#pragma once

#include "../../../Public/Math/Vector3D.h"

struct CollisionData
{
    Vector3D CollisionNormal;
    Vector3D CollisionPoint;
    double PenetrationDepth;
};
