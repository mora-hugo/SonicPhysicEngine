#include "../../Public/Math/Quaternion.h"

#include <array>

#include "../../Public/Math/Vector3D.h"
#include "ofMathConstants.h"

EulerAngle EulerAngle::FromQuaternion(const Quaternion& quaternion)
{
    // Call the quaternion_to_euler function
    auto euler = quaternion_to_euler({quaternion.x, quaternion.y, quaternion.z, quaternion.w});
    return {euler[2], euler[1], euler[0]}; // Adjust the order if necessary
}

std::array<double, 3> quaternion_to_euler(const std::array<double, 4>& q)
{
    double t0 = +2.0 * (q[3] * q[0] + q[1] * q[2]);
    double t1 = +1.0 - 2.0 * (q[0] * q[0] + q[1] * q[1]);
    double roll = std::atan2(t0, t1);

    double t2 = +2.0 * (q[3] * q[1] - q[2] * q[0]);
    t2 = +1.0 > +t2 ? +1.0 : t2;
    t2 = -1.0 > -t2 ? -1.0 : t2;
    double pitch = std::asin(t2);

    double t3 = +2.0 * (q[3] * q[2] + q[0] * q[1]);
    double t4 = +1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]);
    double yaw = std::atan2(t3, t4);

    return {yaw, pitch, roll};
}

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
    return Quaternion(0, vector.GetX(), vector.GetY(), vector.GetZ());
}

Quaternion Quaternion::fromEulerAngle(const EulerAngle& eulerAngle)
{
    double yaw = eulerAngle.yaw;
    double pitch = eulerAngle.pitch;
    double roll = eulerAngle.roll;

    double cy = std::cos(yaw * 0.5);
    double sy = std::sin(yaw * 0.5);
    double cp = std::cos(pitch * 0.5);
    double sp = std::sin(pitch * 0.5);
    double cr = std::cos(roll * 0.5);
    double sr = std::sin(roll * 0.5);

    double qw = cr * cp * cy + sr * sp * sy;
    double qx = sr * cp * cy - cr * sp * sy;
    double qy = cr * sp * cy + sr * cp * sy;
    double qz = cr * cp * sy - sr * sp * cy;

    return Quaternion(qw, qx, qy, qz);
}
