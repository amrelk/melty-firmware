#pragma once
#include <cmath>
#include "rotation.h"

class Translation2d
{
private:
    float x = 0;
    float y = 0;
public:
    Translation2d();
    Translation2d(float x, float y);
    ~Translation2d();

    void setPosition(float x, float y) {setX(x); setY(y);};
    void setX(float x) {this->x = x;}
    void setY(float y) {this->y = y;}

    float norm();
    float getDistance(Translation2d other);
    float getX();
    float getY();
    Rotation2d getAngle();

    Translation2d rotateBy(Rotation2d rhs);

    Translation2d operator-();
    Translation2d operator+(Translation2d rhs);
    Translation2d operator-(Translation2d rhs);
    Translation2d operator*(float rhs);
    Translation2d operator/(float rhs);
};