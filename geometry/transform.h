#pragma once
#include "rotation.h"
#include "translation.h"

class Transform2d
{
private:
    Translation2d translation;
    Rotation2d rotation;
public:
    Transform2d();
    Transform2d(Translation2d translation, Rotation2d rotation);
    Transform2d(float x, float y, float theta);
    ~Transform2d();

    Translation2d getTranslation() { return translation; }
    Rotation2d getRotation() { return rotation; }
};