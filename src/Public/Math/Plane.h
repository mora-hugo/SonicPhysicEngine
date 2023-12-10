#pragma once
#include "Vector3D.h"

struct Plane
{
public:
    Plane(const Vector3D& Normal, const Vector3D& Point) : Normal(Normal), Point(Point) {};
    Vector3D Normal;
    Vector3D Point;
};
