#pragma once
#include <array>
#include <iostream>
#include <string>
using namespace std;

class Matrix4
{
public:
    
    Matrix4();
    Matrix4(double v11, double v12, double v13, double v14,
            double v21, double v22, double v23, double v24,
            double v31, double v32, double v33, double v34,
            double v41, double v42, double v43, double v44);

    void Diagonal();
    
    // Getter for accessing individual elements of the matrix
    double GetMatrix4Element(int row, int col);
    
    // Setter for modifying individual elements of the matrix
    void SetMatrix4Element(int row, int col, double value);

    Matrix4 Add(Matrix4 m);
    Matrix4 Substract(Matrix4 m);
    Matrix4 Multiply(double Scalar);
    Matrix4 Multiply(Matrix4 m);

    operator std::string() const
    {
        return"        0        1        2       3 \n0 | "
        +std::to_string(data[0][0])+" "+std::to_string(data[0][1])+" "+std::to_string(data[0][2])+" "+ std::to_string(data[0][3])+" |"+"\n"+
        "1 | "+std::to_string(data[1][0])+" "+std::to_string(data[1][1])+" "+std::to_string(data[1][2])+" "+ std::to_string(data[1][3])+" |"+"\n"
        "2 | "+std::to_string(data[2][0])+" "+std::to_string(data[2][1])+" "+std::to_string(data[2][2])+" "+ std::to_string(data[2][3])+ " |"+"\n"
        "3 | "+std::to_string(data[3][0])+" "+std::to_string(data[3][1])+" "+std::to_string(data[3][2])+" "+ std::to_string(data[3][3])+ " |"+"\n";
    }

    Matrix4 operator+(Matrix4 m) {
        return this->Add(m);
    }
    
    Matrix4 operator-(const Matrix4 m) {
        return (this->Substract(m));
    }

    Matrix4 operator*(const double Scalar) {
        return (this->Multiply(Scalar));
    }
    
    Matrix4 operator*(const Matrix4 m) {
        return (this->Multiply(m));
    }

private:
    double data[4][4];
};
