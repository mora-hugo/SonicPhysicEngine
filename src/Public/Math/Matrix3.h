#pragma once
#include <array>
#include <iostream>
#include "Vector3D.h"
using namespace std;

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

    operator std::string() const
    {
        return "        0        1        2 \n0 | " +
            std::to_string(data[0][0]) + " " + std::to_string(data[0][1]) + " " + std::to_string(data[0][2]) + " |" + "\n" +
            "1 | " + std::to_string(data[1][0]) + " " + std::to_string(data[1][1]) + " " + std::to_string(data[1][2]) + " |" + "\n" +
            "2 | " + std::to_string(data[2][0]) + " " + std::to_string(data[2][1]) + " " + std::to_string(data[2][2]) + " |" + "\n";
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

private:
    double data[3][3];
};
