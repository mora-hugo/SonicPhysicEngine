#include "./../../Public/Math/Matrix4.h"

#include <complex>

#include "MathFunctions.h"
#include "../../Public/Math/Matrix3.h"

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

//Permet de créer une matrice diagonale
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

double Matrix4::determinant()
{
    double res = 0;

    /* On va utliser la méthode général pour calculer le déterminant de la matrice 4*4
     *
     * On ne recherchera pas de ligne "plus rapide" / avec le plus de 0 (on fera le long de la première colonne)
     *
     *      + - + -
     *    | a b c d |
     * det| e f g h | = a * (a)^1+1 * det| f g h | + e * (e)^2+1 det| b c d | etc.. (pareil pour i et m)
     *    | i j k l |                    | j k l |                  | j k l |
     *    | m n o p |                    | n o p |                  | n o p |
     *                               aussi appelé m11                  m21
     */

    //Déclaration des mineurs (determinants des sous matrices)
    double m11 = Matrix3(MatrixF, MatrixG, MatrixH, MatrixJ, MatrixK, MatrixL, MatrixN, MatrixO, MatrixP).determinant();
    double m21 = Matrix3(MatrixB, MatrixC, MatrixD, MatrixJ, MatrixK, MatrixL, MatrixN, MatrixO, MatrixP).determinant();
    double m31 = Matrix3(MatrixB, MatrixC, MatrixD, MatrixF, MatrixG, MatrixH, MatrixN, MatrixO, MatrixP).determinant();
    double m41 = Matrix3(MatrixB, MatrixC, MatrixD, MatrixF, MatrixG, MatrixH, MatrixJ, MatrixK, MatrixL).determinant();

    //A * m11 - E * m21 + I * m31 - M * m41
    res = MatrixA * m11 - MatrixE * m21 + MatrixI * m31 - MatrixM * m41;
    return res;    
}

Matrix4 Matrix4::Transpose()
{
    //La i ème colonne de notre matrice est la i ème ligne de la transposé de notre matrice
    Matrix4 res = Matrix4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.SetMatrix4Element(i,j, data[j][i]);
        }
    }
    return res;
}

Matrix4 Matrix4::Reverse()
{
    // 1/det * matrice complémentaire
    Matrix4 res = Matrix4();
    double det = determinant();
    
    if (det == 0.0)
    {
        std::cerr << "Your matrix isn't reversable" << std::endl;
        return Matrix4().NullMatrix();
    }

    /*
     * Calcul de la matriceComplémentaire
     *
     *    | a b c d |
     *    | e f g h |  
     *    | i j k l |                  
     *    | m n o p |                    
     *
     * On fait une matrice avec le déterminant de toutes les sous matrice 3x3 en enlevant une ligne et une colonne (On multiplie par -1 à la puissance de la somme i et j qui sont les positions du nombre dans la matrice)
     */

    //Déclaration des mineurs (determinants des sous matrices)
    double m11 = Matrix3(MatrixF,MatrixG,MatrixH,MatrixJ,MatrixK,MatrixL,MatrixN,MatrixO,MatrixP).determinant() * pow(-1, 1+1);
    double m21 = Matrix3(MatrixB,MatrixC,MatrixD,MatrixJ,MatrixK,MatrixL,MatrixN,MatrixO,MatrixP).determinant() * pow(-1, 2+1);
    double m31 = Matrix3(MatrixB,MatrixC,MatrixD,MatrixF,MatrixG,MatrixH,MatrixN,MatrixO,MatrixP).determinant() * pow(-1, 3+1);
    double m41 = Matrix3(MatrixB,MatrixC,MatrixD,MatrixF,MatrixG,MatrixH,MatrixJ,MatrixK,MatrixL).determinant() * pow(-1, 4+1);

    double m12 = Matrix3(MatrixE,MatrixG,MatrixH,MatrixI,MatrixK,MatrixL,MatrixM,MatrixO,MatrixP).determinant() * pow(-1, 1+2);
    double m22 = Matrix3(MatrixA,MatrixC,MatrixD,MatrixI,MatrixK,MatrixL,MatrixM,MatrixO,MatrixP).determinant() * pow(-1, 2+2);
    double m32 = Matrix3(MatrixA,MatrixC,MatrixD,MatrixE,MatrixG,MatrixH,MatrixM,MatrixO,MatrixP).determinant() * pow(-1, 3+2);
    double m42 = Matrix3(MatrixA,MatrixC,MatrixD,MatrixE,MatrixG,MatrixH,MatrixI,MatrixK,MatrixL).determinant() * pow(-1, 4+2);

    double m13 = Matrix3(MatrixE,MatrixF,MatrixH,MatrixI,MatrixJ,MatrixL,MatrixM,MatrixN,MatrixP).determinant() * pow(-1, 1+3);
    double m23 = Matrix3(MatrixA,MatrixB,MatrixD,MatrixI,MatrixJ,MatrixL,MatrixM,MatrixN,MatrixP).determinant() * pow(-1, 2+3);
    double m33 = Matrix3(MatrixA,MatrixB,MatrixD,MatrixE,MatrixF,MatrixH,MatrixM,MatrixN,MatrixP).determinant() * pow(-1, 3+3);
    double m43 = Matrix3(MatrixA,MatrixB,MatrixD,MatrixE,MatrixF,MatrixH,MatrixI,MatrixJ,MatrixL).determinant() * pow(-1, 4+3);

    double m14 = Matrix3(MatrixE,MatrixF,MatrixG,MatrixI,MatrixJ,MatrixK,MatrixM,MatrixN,MatrixO).determinant() * pow(-1, 1+4);
    double m24 = Matrix3(MatrixA,MatrixB,MatrixC,MatrixI,MatrixJ,MatrixK,MatrixM,MatrixN,MatrixO).determinant() * pow(-1, 2+4);
    double m34 = Matrix3(MatrixA,MatrixB,MatrixC,MatrixE,MatrixF,MatrixG,MatrixM,MatrixN,MatrixO).determinant() * pow(-1, 3+4);
    double m44 = Matrix3(MatrixA,MatrixB,MatrixC,MatrixE,MatrixF,MatrixG,MatrixI,MatrixJ,MatrixK).determinant() * pow(-1, 4+4);

    Matrix4 ComplementaryMatrix = Matrix4(m11,m12,m13,m14,m21,m22,m23,m24,m31,m32,m33,m34,m41,m42,m43,m44).Transpose();
    
    res = ComplementaryMatrix * (1/det);
    
    return res;
}

Matrix4 Matrix4::NullMatrix()
{
    Matrix4 res = Matrix4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.data[i][j] = NULL;
        }
    }
    return res;
}
