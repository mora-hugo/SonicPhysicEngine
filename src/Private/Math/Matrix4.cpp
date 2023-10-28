#include "./../../Public/Math/Matrix4.h"

Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = 0.0;
        }
    }
}

Matrix4::Matrix4(double v11, double v12, double v13, double v14, double v21, double v22, double v23, double v24,
    double v31, double v32, double v33, double v34, double v41, double v42, double v43, double v44)
{
    data[0][0] = v11;
    data[0][1] = v12;
    data[0][2] = v13;
    data[0][3] = v14;
    data[1][0] = v21;
    data[1][1] = v22;
    data[1][2] = v23;
    data[1][3] = v24;
    data[2][0] = v31;
    data[2][1] = v32;
    data[2][2] = v33;
    data[2][3] = v34;
    data[3][0] = v41;
    data[3][1] = v42;
    data[3][2] = v43;
    data[3][3] = v44;
}

double Matrix4::GetMatrix4Element(int row, int col)
{
    if (row >= 0 && row < 4 && col >= 0 && col < 4) {
        return data[row][col];
    } else {
        std::cerr << "Invalid indices for getElement()" << std::endl;
        return 0.0; // Return a default value in case of invalid indices
    }
}

void Matrix4::SetMatrix4Element(int row, int col, double value)
{
    if (row >= 0 && row < 4 && col >= 0 && col < 4) {
        data[row][col] = value;
    } else {
        std::cerr << "Invalid indices for setElement()" << std::endl;
    }
}
