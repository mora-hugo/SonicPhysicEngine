#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <cmath>
#include "./Vector3D.h"

class Quaternion {
public:
    double w, x, y, z;

    Quaternion(double real, double i, double j, double k);

    // Quaternion multiplication
    Quaternion operator*(const Quaternion& other) const;

    // Quaternion conjugate
    Quaternion conjugate() const;

    // Function to create and return the identity quaternion
    static Quaternion identity();

    // Quaternion norm (magnitude)
    double norm() const;

    // Normalize the quaternion
    void normalize();

    // Function to negate the quaternion
    Quaternion negate() const;

    // Function to calculate the difference between two quaternions
    Quaternion difference(const Quaternion& other) const;
    
    // Function to compute the scalar (dot) product of two quaternions
    double scalarProduct(const Quaternion& other) const;

    // Function to exponentiate the quaternion
    Quaternion exponentiation() const;

    // Function to add two quaternions
    Quaternion operator+(const Quaternion& other) const;

    // Function to subtract two quaternions
    Quaternion operator-(const Quaternion& other) const;

    //Function that create a Quaternion with a Vector
    static Quaternion fromVector(const Vector3D& vector);
};

#endif
