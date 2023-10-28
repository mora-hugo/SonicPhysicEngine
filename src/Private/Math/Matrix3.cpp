#include "./../../Public/Math/Matrix3.h"

Matrix3::Matrix3()
{
}

Matrix3::Matrix3(Vector3D& v1, Vector3D& v2, Vector3D& v3)
{
    columns[0] = v1;
    columns[1] = v2;
    columns[2] = v3;
}

Vector3D Matrix3::GetColumn(int col) const
{
    if (col >= 0 && col < 3) {
        return columns[col];
    } else {
        cerr << "Invalid column index for getColumn()" << endl;
        return Vector3D();
    }
}

void Matrix3::SetColumn(int col, const Vector3D& vec)
{
    if (col >= 0 && col < 3) {
        columns[col] = vec;
    } else {
        cerr << "Invalid column index for setColumn()" << endl;
    }
}
