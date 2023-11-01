#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <cmath>

class Quaternion {
public:
    double w, x, y, z;

    Quaternion(double real, double i, double j, double k);

    // Quaternion multiplication
    Quaternion operator*(const Quaternion& other) const;

    // Quaternion conjugate
    Quaternion conjugate() const;

    // Quaternion norm (magnitude)
    double norm() const;

    // Normalize the quaternion
    void normalize();
};

#endif
