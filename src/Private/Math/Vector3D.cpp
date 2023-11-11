#include "../../Public/Math/Vector3D.h"
Vector3D::Vector3D(const double X, const double Y, const double Z, const double W) : X(X), Y(Y), Z(Z), W(W)
{
    
}

Vector3D::Vector3D(const glm::vec3& vec3) : X(vec3.x), Y(vec3.y), Z(vec3.z), W(1)
{
    
}

Vector3D Vector3D::Add(const Vector3D& Vector) const
{
    return Vector3D(X+Vector.GetX(),Y+Vector.GetY(),Z+Vector.GetZ(),W);
}

Vector3D Vector3D::Sub(const Vector3D& Vector) const
{
    return Vector3D(X-Vector.GetX(),Y-Vector.GetY(),Z-Vector.GetZ(),W);
}

Vector3D Vector3D::Multiply(const double Scalar) const
{
    return Vector3D(X*Scalar,Y*Scalar,Z*Scalar);
}

Vector3D Vector3D::Divide(const double Scalar) const
{
    //assert(Scalar == 0,"Division by zero is impossible");

    return Multiply(1/Scalar);
}

Vector3D Vector3D::Negate() const
{
    return Multiply(-1);
}

Vector3D Vector3D::Normalize() const
{
    if (this->GetX() == 0 && this->GetY() == 0 && this->GetZ() == 0)
    {
        return Vector3D();
    }
    return Multiply(1/Magnitude());
}

double Vector3D::Magnitude() const
{
    if(MagnitudeSquared() == 0)
        return 0;
    
    return sqrt(MagnitudeSquared());
}

double Vector3D::MagnitudeSquared() const
{
    return pow(X,2)+pow(Y,2)+pow(Z,2);
}

Vector3D Vector3D::ComponentProduct(const Vector3D& Vector) const
{
    return Vector3D(X * Vector.X, Y * Vector.Y, Z * Vector.Z, W * Vector.W);
}

double Vector3D::DotProduct(const Vector3D& Vector) const
{
    return (X * Vector.X + Y * Vector.Y + Z * Vector.Z);

}

Vector3D Vector3D::CrossProduct(const Vector3D& Vector) const
{
    const double resultX = Y * Vector.Z - Z * Vector.Y;
    const double resultY = Z * Vector.X - X * Vector.Z;
    const double resultZ = X * Vector.Y - Y * Vector.X;
    
    return Vector3D(resultX, resultY, resultZ, W);
}

float Vector3D::Distance(const Vector3D& Vector) const
{
    // get distance beetween two points
    return Sub(Vector).Magnitude();
    
}


Vector3D Vector3D::Zero()
{
    return Vector3D();
}

Vector3D Vector3D::fromQuaternion(const Quaternion& quaternion)
{
    return Vector3D(quaternion.x, quaternion.y, quaternion.z);
}

