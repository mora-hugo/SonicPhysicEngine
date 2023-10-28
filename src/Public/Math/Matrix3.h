#pragma once
#include <array>
#include <iostream>
using namespace std;

class Matrix3
{
public:
    
    Matrix3();
    Matrix3(double v11, double v12, double v13,
            double v21, double v22, double v23,
            double v31, double v32, double v33);

    
    // Getter for accessing individual elements of the matrix
    double GetMatrix3Element(int row, int col);
    
    // Setter for modifying individual elements of the matrix
    void SetMatrix3Element(int row, int col, double value);

private:
    double data[3][3];
};
