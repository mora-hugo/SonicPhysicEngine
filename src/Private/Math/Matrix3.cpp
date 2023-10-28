#include "./../../Public/Math/Matrix3.h"

Matrix3::Matrix3()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = 0.0;
        }
    }
}

Matrix3::Matrix3(double v11, double v12, double v13, double v21, double v22, double v23, double v31, double v32,
    double v33)
{
    data[0][0] = v11;
    data[0][1] = v12;
    data[0][2] = v13;
    data[1][0] = v21;
    data[1][1] = v22;
    data[1][2] = v23;
    data[2][0] = v31;
    data[2][1] = v32;
    data[2][2] = v33;
}

double Matrix3::GetMatrix3Element(int row, int col)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return data[row][col];
    } else {
        cerr << "Invalid indices for getElement()" << endl;
        return 0.0; // Return a default value in case of invalid indices
    }
}

void Matrix3::SetMatrix3Element(int row, int col, double value)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        data[row][col] = value;
    } else {
        cerr << "Invalid indices for setElement()" << endl;
    }
}
