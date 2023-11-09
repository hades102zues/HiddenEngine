#include "camera.h"


Camera::Camera(ProjectionType type, glm::vec3 position, glm::vec3 direction, glm::vec3 up, float pitch, float yaw) {
    mType = type;
    mPosition = position;
    mDirection = direction;
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);
    mPitch = 0.0f;
    mYaw = 0.0f;


    // the projection matrix changes based on what the camera type is

}

glm::mat4 Camera::Matrix() {
    // should combine the projection * view
    // return the resultant matrix
    auto matrix = glm::mat4(1.0f);
    return matrix;
}