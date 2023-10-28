#pragma once
#include <array>
#include <iostream>
using namespace std;

class Matrix4
{
public:
    
    Matrix4();
    Matrix4(double v11, double v12, double v13, double v14,
            double v21, double v22, double v23, double v24,
            double v31, double v32, double v33, double v34,
            double v41, double v42, double v43, double v44);

    
    // Getter for accessing individual elements of the matrix
    double GetMatrix4Element(int row, int col);
    
    // Setter for modifying individual elements of the matrix
    void SetMatrix4Element(int row, int col, double value);

private:
    double data[4][4];
};
