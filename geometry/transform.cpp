#include "transform.h"

Transform2d::Transform2d() {}

Transform2d::Transform2d(Translation2d translation, Rotation2d rotation): translation(translation), rotation(rotation) {}

Transform2d::Transform2d(float x, float y, float theta): translation(x, y), rotation(theta) {}

Transform2d::~Transform2d() {}
