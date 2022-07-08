#include <cstdint>
#include "geometry/rotation.h"
#include "geometry/translation.h"

class MeltyController
{
private:
    Rotation2d estCurrentRotation;
    Rotation2d estRotationalVel;

    uint32_t lastStepMillis = 0;

    static constexpr float accelRadius = 0.01; //m
    static constexpr float wheelRadius = 0.04; //m
public:
    struct wheel_vels
    {
        float leftVel; // m/s
        float rightVel; // m/s
    };
    
    MeltyController();
    ~MeltyController();
    void periodic();
    void updateAcceleration(float accel);
    void updateWheelVels(wheel_vels vels);
    void setTargetVel(Translation2d vector);
    wheel_vels getTargetVels();
};