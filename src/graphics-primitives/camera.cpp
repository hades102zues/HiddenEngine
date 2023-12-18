#include "camera.h"
#include <glm/gtc/matrix_transform.hpp> 
#include "../engine-core/logger/logger.h"


Camera::Camera() {
    HIDDEN_WARN("Default Constructor for Camera called. Camera instance will be malformed.");
}
Camera::Camera(ProjectionType type, glm::vec3 position, glm::vec3 at, float windowAspectRatio) {
    mType = type;
    mPosition = position;
    mLookingAt = at;
    mAspectRatio = windowAspectRatio;

    CalculateView();
    CalculateProjection();
    
}

void Camera::CalculateView() {

    glm::vec3 arbitraryUp = glm::vec3(0.0f, 1.0f, 0.0f);
    mView = glm::lookAt(mPosition, mLookingAt, arbitraryUp);

}
void Camera::CalculateProjection() {

    if (mType == ProjectionType::PERSPECTIVE) {

        float fov = 45; //degrees
        float distanceToNearPlane = 0.1f;
        float distanceToFarPlane = 100.0f;
        mProjection = glm::perspective(glm::radians(fov), mAspectRatio, distanceToNearPlane, distanceToFarPlane);

    } else {

    }
    
}

void Camera::Update() {

}



glm::mat4 Camera::GetProjectionMatrix() {
    return mProjection;
}

glm::mat4 Camera::GetViewMatrix() {
    return mView;
}