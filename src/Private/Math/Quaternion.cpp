#include "../../Math/Quaternion.h"

Quaternion::Quaternion(double real, double i, double j, double k) : w(real), x(i), y(j), z(k) {}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    double realPart = w * other.w - x * other.x - y * other.y - z * other.z;
    double iPart = w * other.x + x * other.w + y * other.z - z * other.y;
    double jPart = w * other.y - x * other.z + y * other.w + z * other.x;
    double kPart = w * other.z + x * other.y - y * other.x + z * other.w;
    return Quaternion(realPart, iPart, jPart, kPart);
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(w, -x, -y, -z);
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
