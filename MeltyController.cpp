#include "MeltyController.h"

MeltyController::MeltyController() {}

MeltyController::~MeltyController() {}

void MeltyController::periodic() {
    estCurrentRotation =  estRotationalVel;
}

void MeltyController::updateAcceleration(float accel) {

};
void MeltyController::updateWheelVels(wheel_vels vels) {};
void MeltyController::setTargetVel(Translation2d vector) {};
MeltyController::wheel_vels MeltyController::getTargetVels() {};
