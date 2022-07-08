#include "pose.h"

Pose2d::Pose2d() {}

Pose2d::Pose2d(Translation2d translation, Rotation2d rotation): translation(translation), rotation(rotation) {}

Pose2d::Pose2d(float x, float y, float theta) {
    translation.setPosition(x, y);
    rotation = Rotation2d(theta);
}

Pose2d::~Pose2d() {}

Pose2d Pose2d::exp(Twist2d twist) {
    /*
     * although it looks somewhat different, this method does simplify down to ICC
     * dx = (d_l + d_r)/2
     * dtheta  = (d_r - d_l)/l
     * R = dx/dtheta = (l/2)(d_l + d_r)/(d_r - d_l)
     * 
     * tx = dx * sin(dtheta) / dtheta = Rsin(dtheta)
     * ty = dx * (1 - cos(dtheta)) / dtheta = R(1-cos(dtheta))
     * these are the ICC equations for theta = 0
     * 
     * the operator+ function does the math to rotate the transformation, so we can let theta stay 0
    */
    
    float s;
    float c;

    // approximation for very small values of dtheta
    // this is useful because we spend a fair amount of time driving very close to
    // straight forward and trigonometry is computationally expensive
    if (fabsf(twist.dtheta) < 1e-6) {
        s = 1.0;
        c = 0.0;
    } else {
        s = sinf(twist.dtheta) / twist.dtheta;
        c = (1 - cosf(twist.dtheta)) / twist.dtheta;
    }

    Transform2d transform = Transform2d(
        Translation2d(twist.dx * s, twist.dx * c),
        Rotation2d(cosf(twist.dtheta), sinf(twist.dtheta))
    );

    return operator+(transform);
}

Twist2d Pose2d::log(Pose2d end) {
    Transform2d transform = end - *this;
    float dtheta = transform.getRotation().getRadians();

    float htbt;
    if (fabsf(transform.getRotation().getCos() - 1) < 1e-6) {
        htbt = 1.0 - 1.0 / 12.0 * dtheta * dtheta;
    } else {
        htbt = -((dtheta / 2.0) * transform.getRotation().getSin()) / (transform.getRotation().getCos() - 1);
    }

    Translation2d translation = transform.getTranslation().rotateBy(Rotation2d(htbt, -dtheta/2.0)) * hypotf(htbt, dtheta/2.0);

    return Twist2d{translation.getX(), dtheta};
}

Pose2d Pose2d::operator+(Transform2d rhs) {
    return Pose2d(
        translation + rhs.getTranslation().rotateBy(rotation),
        rotation + rhs.getRotation()
    );
}

Transform2d Pose2d::operator-(Pose2d rhs) {
    return Transform2d(
        (getTranslation() - rhs.getTranslation()).rotateBy(-rhs.getRotation()),
        getRotation() - rhs.getRotation()
    );
}