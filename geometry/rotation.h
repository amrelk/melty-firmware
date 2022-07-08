#pragma once
#include <cmath>

class Rotation2d
{
private:
    float cos;
    float sin;
    float value;
public:
    Rotation2d();
    Rotation2d(float value);
    Rotation2d(float x, float y);
    ~Rotation2d();

    float getRadians();
    float getDegrees();
    float getCos();
    float getSin();
    float getTan();

    Rotation2d rotateBy(Rotation2d other);
    Rotation2d operator-();
    Rotation2d operator+(Rotation2d rhs);
    Rotation2d operator-(Rotation2d rhs);
    Rotation2d operator*(float rhs);

    Rotation2d operator+=(Rotation2d rhs);
    Rotation2d operator-=(Rotation2d rhs);
    Rotation2d operator*=(Rotation2d rhs);
};