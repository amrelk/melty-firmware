#pragma once

#include <cmath>
#include "translation.h"
#include "rotation.h"
#include "transform.h"

struct Twist2d {
    float dx;
    float dtheta;
};

class Pose2d
{
private:
    Translation2d translation;
    Rotation2d rotation;
public:
    Pose2d();
    Pose2d(float x, float y, float theta);
    Pose2d(Translation2d translation, Rotation2d rotation);
    ~Pose2d();

    Translation2d getTranslation() {return translation;}
    Rotation2d getRotation() {return rotation;}

    void setX(float x) {translation.setX(x);}
    void setY(float y) {translation.setY(y);}
    void setTheta(float rad) {rotation = Rotation2d(rad);}

    // return this pose translated by the twist
    Pose2d exp(Twist2d twist);

    // return the twist that gets us from this pose to the end pose
    Twist2d log(Pose2d end);

    Pose2d operator+(Transform2d rhs);
    Transform2d operator-(Pose2d rhs);
};