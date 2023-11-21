#pragma once
#include <array>
#include <iostream>
#include <string>
using namespace std;

#define MatrixA data[0][0]
#define MatrixB data[0][1]
#define MatrixC data[0][2]
#define MatrixD data[0][3]
#define MatrixE data[1][0]
#define MatrixF data[1][1]
#define MatrixG data[1][2]
#define MatrixH data[1][3]
#define MatrixI data[2][0]
#define MatrixJ data[2][1]
#define MatrixK data[2][2]
#define MatrixL data[2][3]
#define MatrixM data[3][0]
#define MatrixN data[3][1]
#define MatrixO data[3][2]
#define MatrixP data[3][3]

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

    double determinant();
    Matrix4 Transpose();
    Matrix4 Reverse();

    operator std::string() const
    {
        return"        0        1        2       3 \n0 | "
        +std::to_string(MatrixA)+" "+std::to_string(MatrixB)+" "+std::to_string(MatrixC)+" "+ std::to_string(MatrixD)+" |"+"\n"+
        "1 | "+std::to_string(MatrixE)+" "+std::to_string(MatrixF)+" "+std::to_string(MatrixG)+" "+ std::to_string(MatrixH)+" |"+"\n"
        "2 | "+std::to_string(MatrixI)+" "+std::to_string(MatrixJ)+" "+std::to_string(MatrixK)+" "+ std::to_string(MatrixL)+ " |"+"\n"
        "3 | "+std::to_string(MatrixM)+" "+std::to_string(MatrixN)+" "+std::to_string(MatrixO)+" "+ std::to_string(MatrixP)+ " |"+"\n";
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

    Matrix4 NullMatrix();
    
private:
    double data[4][4];

};
