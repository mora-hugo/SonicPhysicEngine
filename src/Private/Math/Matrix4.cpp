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

void Matrix4::Diagonal()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = 0.0;
        }
    }
    data[0][0] = 1;
    data[1][1] = 1;
    data[2][2] = 1;
    data[3][3] = 1;
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

Matrix4 Matrix4::Add(Matrix4 m)
{
    Matrix4 res = Matrix4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.SetMatrix4Element(i,j, data[i][j] + m.GetMatrix4Element(i, j));
        }
    }
    return res;
}

Matrix4 Matrix4::Substract(Matrix4 m)
{
    Matrix4 res = Matrix4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.SetMatrix4Element(i,j, data[i][j] - m.GetMatrix4Element(i, j));
        }
    }
    return res;
}

Matrix4 Matrix4::Multiply(double Scalar)
{
    Matrix4 res = Matrix4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.SetMatrix4Element(i,j, data[i][j] * Scalar);
        }
    }
    return res;
}

Matrix4 Matrix4::Multiply(Matrix4 m)
{
    Matrix4 res = Matrix4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            
            /*
            * | a11 a12 a13 a14 |     | b11 b12 b13 b14 |   | c11 c12 c13 c14 |
            * | a21 a22 a23 a24 |  *  | b21 b22 b23 b24 | = | c21 c22 c23 c24 |
            * | a31 a32 a33 a34 |     | b31 b32 b33 b34 |   | c31 c32 c33 c34 |
            * | a41 a42 a43 a44 |     | b41 b42 b43 b44 |   | c41 c42 c43 c44 |
            *
            * démo :
            * i = 1
            * j = 3
            * c13 = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43
            * cij = ai1 * b1j + ai2 * b2j + ai3 * b3j + ai4 * b4j
            */
            
            double value = data[i][0] * m.GetMatrix4Element(0, j) +
                           data[i][1] * m.GetMatrix4Element(1,j) +
                           data[i][2] * m.GetMatrix4Element(2, j) +
                           data[i][3] * m.GetMatrix4Element(3,j);
            
            res.SetMatrix4Element(i,j, value );
        }
    }
    return res;
}
