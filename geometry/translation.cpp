#include "translation.h"

Translation2d::Translation2d() {}

Translation2d::Translation2d(float x, float y) : x(x), y(y) {}

Translation2d::~Translation2d() {}

float Translation2d::norm() {
    return sqrtf(x*x + y*y);
}

float Translation2d::getDistance(Translation2d other) {
    return hypotf(other.x - x, other.y - y);
}

float Translation2d::getX() {
    return x;
}

float Translation2d::getY() {
    return y;
}

Rotation2d Translation2d::getAngle() {
    return Rotation2d(x, y);
}

Translation2d Translation2d::rotateBy(Rotation2d rhs) {
    return Translation2d(x * rhs.getCos() - y * rhs.getSin(), x * rhs.getSin() + y * rhs.getCos());
}

Translation2d Translation2d::operator-() {
    return Translation2d(-x, -y);
}

Translation2d Translation2d::operator+(Translation2d rhs) {
    return Translation2d(x + rhs.x, y + rhs.y);
}

Translation2d Translation2d::operator-(Translation2d rhs) {
    return Translation2d(x - rhs.x, y - rhs.y);
}

Translation2d Translation2d::operator*(float rhs) {
    return Translation2d(x * rhs, y * rhs);
}

Translation2d Translation2d::operator/(float rhs) {
    return Translation2d(x / rhs, y / rhs);
}