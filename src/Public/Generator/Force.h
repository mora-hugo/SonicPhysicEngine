﻿#pragma once
#include "ForceGenerator.h"
#include "../../Public/Math/Vector3D.h"
class GameObject;
class Force
{
public:
    Vector3D movement;
    double lifetime;
    ForceType type;

    Force(const Vector3D& movement, double lifetime, ForceType type);
};
