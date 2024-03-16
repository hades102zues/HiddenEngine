#include "camera.h"
#include <glm/gtc/matrix_transform.hpp> 
#include "../engine-core/logger/logger.h"


Camera::Camera() {
    HIDDEN_WARN("Default Constructor for Camera called. Camera instance will be malformed.");
}
Camera::Camera(ProjectionType type, glm::vec3 position, float windowAspectRatio) {
    mType = type;
    mPosition = position;
    mAspectRatio = windowAspectRatio;

    CalculateView();
    CalculateProjection();
    
}

void Camera::CalculateView() {

    glm::vec3 arbitraryUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 pointInFrontCamera = mPosition + glm::vec3(0.0f, 0.0f, -1.0f);
    mView = glm::lookAt(mPosition, pointInFrontCamera, arbitraryUp);

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

void Camera::MoveCameraRight(float dt) {
    glm::vec3 inFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 arbitraryUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 offset = glm::normalize(glm::cross(inFront, arbitraryUp)); //right vector (a, 0, 0)

    float moved = mSpeed * dt;
    offset *= moved;

    mPosition += offset;

    CalculateView();

}
void Camera::MoveCameraLeft(float dt) {
    glm::vec3 inFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 arbitraryUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 offset = glm::normalize(glm::cross(inFront, arbitraryUp)); //right vector (a, 0, 0)

    float moved = mSpeed * dt;
    offset *= moved;

    mPosition -= offset;

    CalculateView();

}
void Camera::MoveCameraForward(float dt) {

    glm::vec3 offset = glm::vec3(0.0f, 0.0f, -1.0f);
    float moved = mSpeed * dt;
    offset = moved * offset;

    mPosition += offset;

    CalculateView();

}
void Camera::MoveCameraBackward(float dt) {

    glm::vec3 offset = glm::vec3(0.0f, 0.0f, -1.0f);
    float moved = mSpeed* dt;
    offset = moved * offset;

    mPosition -= offset;

    CalculateView();
}

void Camera::MoveCameraUp(float dt) {
    glm::vec3 offset = glm::vec3(0.0f, 1.0f, 0.0f);
    float moved = mSpeed * dt;
    offset *= moved;
    mPosition += offset;

    CalculateView();
}

void Camera::MoveCameraDown(float dt) {
    glm::vec3 offset = glm::vec3(0.0f, 1.0f, 0.0f);
    float moved = mSpeed * dt;
    offset *= moved;
    mPosition -= offset;

    CalculateView();
}


void Camera::PitchCamera() {

}
glm::mat4 Camera::GetProjectionMatrix() {
    return mProjection;
}

glm::mat4 Camera::GetViewMatrix() {
    return mView;
}