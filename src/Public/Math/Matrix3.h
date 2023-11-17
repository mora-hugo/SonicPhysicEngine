#pragma once
#include <array>
#include <iostream>
#include "Vector3D.h"
using namespace std;

#define A data[0][0]
#define B data[0][1]
#define C data[0][2]
#define D data[1][0]
#define E data[1][1]
#define F data[1][2]
#define G data[2][0]
#define H data[2][1]
#define I data[2][2]

class Matrix3
{
public:
    
    Matrix3();
    Matrix3(double v11, double v12, double v13,
            double v21, double v22, double v23,
            double v31, double v32, double v33);

    void Diagonal();
    
    double GetMatrix3Element(int row, int col);
    void SetMatrix3Element(int row, int col, double value);

    Matrix3 Add(Matrix3 m);
    Matrix3 Substract(Matrix3 m);
    Matrix3 Multiply(double Scalar);
    Matrix3 Multiply(Matrix3 m);
    Vector3D Multiply(Vector3D v);

    double determinant();
    Matrix3 Transpose();
    Matrix3 Reverse();

    operator std::string() const
    {
        return "        0        1        2 \n0 | " +
            std::to_string(A) + " " + std::to_string(B) + " " + std::to_string(C) + " |" + "\n" +
            "1 | " + std::to_string(D) + " " + std::to_string(E) + " " + std::to_string(F) + " |" + "\n" +
            "2 | " + std::to_string(G) + " " + std::to_string(H) + " " + std::to_string(I) + " |" + "\n";
    }

    Matrix3 operator+(Matrix3 m) {
        return this->Add(m);
    }
    
    Matrix3 operator-(const Matrix3 m) {
        return (this->Substract(m));
    }

    Matrix3 operator*(const double Scalar) {
        return (this->Multiply(Scalar));
    }
    
    Matrix3 operator*(const Matrix3 m) {
        return (this->Multiply(m));
    }

    Vector3D operator*(const Vector3D v) {
        return (this->Multiply(v));
    }

    Matrix3 CreateRotationMatrix(Quaternion q);

private:
    double data[3][3];

    Matrix3 NullMatrix();
};
