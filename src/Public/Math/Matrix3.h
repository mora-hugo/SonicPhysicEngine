#pragma once
#include <array>
#include <iostream>
#include "Vector3D.h"
using namespace std;

class Matrix3
{
public:
    
    Matrix3();
    Matrix3(Vector3D& v1, Vector3D& v2, Vector3D& v3);

    Vector3D GetColumn(int col) const;

    void SetColumn(int col, const Vector3D& vec);

private:
    Vector3D columns[3];
};
