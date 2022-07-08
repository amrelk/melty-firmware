#include "rotation.h"

Rotation2d::Rotation2d(): cos(1), sin(0), value(0) {}

Rotation2d::Rotation2d(float value) : value(value) {
    cos = cosf(value);
    sin = sinf(value);
}

Rotation2d::Rotation2d(float x, float y) {
    float mag = hypotf(x, y);
    if (mag > 1e-6) {
        sin = y / mag;
        cos = x / mag;
    } else {
        sin = 0;
        cos = 1;
    }
    value = atan2f(sin, cos);
}

float Rotation2d::getRadians() {
    return value;
}

float Rotation2d::getDegrees() {
    return value * (180.0/3.141592653589793238463);
}

float Rotation2d::getCos() {
    return cos;
}

float Rotation2d::getSin() {
    return sin;
}

float Rotation2d::getTan() {
    return sin / cos;
}

Rotation2d Rotation2d::rotateBy(Rotation2d other) {
    return Rotation2d(cos * other.cos - sin * other.sin, cos * other.sin + sin * other.cos);
}

Rotation2d Rotation2d::operator-() {
    return Rotation2d(-value);
}

Rotation2d Rotation2d::operator+(Rotation2d rhs) {
    return rotateBy(rhs);
}

Rotation2d Rotation2d::operator-(Rotation2d rhs) {
    return rotateBy(-rhs);
}

Rotation2d Rotation2d::operator*(float rhs) {
    return Rotation2d(value*rhs);
}

Rotation2d Rotation2d::operator+=(Rotation2d rhs) {
    cos = cos * rhs.cos - sin * rhs.sin;
    sin = cos * rhs.sin + sin * rhs.cos;
}

Rotation2d Rotation2d::operator-=(Rotation2d rhs) {}
Rotation2d Rotation2d::operator*=(Rotation2d rhs) {}

Rotation2d::~Rotation2d() {}