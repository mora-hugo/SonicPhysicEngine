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

void Matrix3::Diagonal()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = 0.0;
        }
    }
    data[0][0] = 1;
    data[1][1] = 1;
    data[2][2] = 1;
}

double Matrix3::GetMatrix3Element(int row, int col)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return data[row][col];
    } else {
        std::cerr << "Invalid indices for getElement()" << std::endl;
        return 0.0; // Return a default value in case of invalid indices
    }
}

void Matrix3::SetMatrix3Element(int row, int col, double value)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        data[row][col] = value;
    } else {
        std::cerr << "Invalid indices for setElement()" << std::endl;
    }
}

Matrix3 Matrix3::Add(Matrix3 m)
{
    Matrix3 res = Matrix3();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res.SetMatrix3Element(i, j, data[i][j] + m.GetMatrix3Element(i, j));
        }
    }
    return res;
}


Matrix3 Matrix3::Substract(Matrix3 m)
{
    Matrix3 res = Matrix3();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res.SetMatrix3Element(i,j, data[i][j] - m.GetMatrix3Element(i, j));
        }
    }
    return res;
}

Matrix3 Matrix3::Multiply(double Scalar)
{
    Matrix3 res = Matrix3();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res.SetMatrix3Element(i,j, data[i][j] * Scalar);
        }
    }
    return res;
}

Matrix3 Matrix3::Multiply(Matrix3 m)
{
    Matrix3 res = Matrix3();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            /*
            * | a11 a12 a13 |     | b11 b12 b13 |   | c11 c12 c13 |
            * | a21 a22 a23 |  *  | b21 b22 b23 | = | c21 c22 c23 |
            * | a31 a32 a33 |     | b31 b32 b33 |   | c31 c32 c33 |
            *
            * démo :
            * i = 1
            * j = 3
            * c13 = a11 * b13 + a12 * b23 + a13 * b33
            * cij = ai1 * b1j + ai2 * b2j + ai3 * b3j
            */
            
            double value = data[i][0] * m.GetMatrix3Element(0, j) +
                           data[i][1] * m.GetMatrix3Element(1,j) +
                           data[i][2] * m.GetMatrix3Element(2, j);
            
            res.SetMatrix3Element(i,j, value );
        }
    }
    return res;
}
