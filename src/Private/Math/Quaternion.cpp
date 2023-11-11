#include "../../Public/Math/Quaternion.h"
#include "../../Public/Math/Vector3D.h"

Quaternion::Quaternion(double real, double i, double j, double k) : w(real), x(i), y(j), z(k) {}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    double realPart = w * other.w - x * other.x - y * other.y - z * other.z;
    double iPart = w * other.x + x * other.w + y * other.z - z * other.y;
    double jPart = w * other.y - x * other.z + y * other.w + z * other.x;
    double kPart = w * other.z + x * other.y - y * other.x + z * other.w;
    return Quaternion(realPart, iPart, jPart, kPart);
}

Quaternion Quaternion::operator*(double scalar) const {
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::identity() {
    return Quaternion(1.0, 0.0, 0.0, 0.0);
}

double Quaternion::norm() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

void Quaternion::normalize() {
    double magnitude = norm();
    if (magnitude > 0) {
        w /= magnitude;
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }
}

Quaternion Quaternion::negate() const {
    return Quaternion(-w, -x, -y, -z);
}

Quaternion Quaternion::difference(const Quaternion& other) const {
    // To calculate the difference, we find the quaternion that represents the rotation from "other" to "this".
    // The difference quaternion is obtained by multiplying "this" with the conjugate of "other".
    Quaternion conjugateOther = other.conjugate();
    return (*this) * conjugateOther;
}

double Quaternion::scalarProduct(const Quaternion& other) const {
    return w * other.w + x * other.x + y * other.y + z * other.z;
}

Quaternion Quaternion::exponentiation() const {
    double norm = this->norm(); //sqrt(w * w + x * x + y * y + z * z);
    double expReal = cos(norm);
    double expFactor = (norm > 0.0) ? sin(norm) / norm : 1.0;

    return Quaternion(expReal, x * expFactor, y * expFactor, z * expFactor);
}

Quaternion Quaternion::operator+(const Quaternion& other) const {
    return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
    return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
}

Quaternion Quaternion::fromVector(const Vector3D& vector) {
    return Quaternion(0.0, vector.GetX(), vector.GetY(), vector.GetZ());
}
