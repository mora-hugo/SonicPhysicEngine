#pragma once
#include <array>
#include <iostream>
#include <string>
using namespace std;

#define A data[0][0]
#define B data[0][1]
#define C data[0][2]
#define D data[0][3]
#define E data[1][0]
#define F data[1][1]
#define G data[1][2]
#define H data[1][3]
#define I data[2][0]
#define J data[2][1]
#define K data[2][2]
#define L data[2][3]
#define M data[3][0]
#define N data[3][1]
#define O data[3][2]
#define P data[3][3]

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
        +std::to_string(A)+" "+std::to_string(B)+" "+std::to_string(C)+" "+ std::to_string(D)+" |"+"\n"+
        "1 | "+std::to_string(E)+" "+std::to_string(F)+" "+std::to_string(G)+" "+ std::to_string(H)+" |"+"\n"
        "2 | "+std::to_string(I)+" "+std::to_string(J)+" "+std::to_string(K)+" "+ std::to_string(L)+ " |"+"\n"
        "3 | "+std::to_string(M)+" "+std::to_string(N)+" "+std::to_string(O)+" "+ std::to_string(P)+ " |"+"\n";
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

    Matrix4 NullMatrix();
};
