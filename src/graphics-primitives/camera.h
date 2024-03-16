#pragma once

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>


enum class ProjectionType {
    PERSPECTIVE = 0,
    ORTHOGRAPHIC = 1
};

class Camera {
private:

    // Projection
    ProjectionType mType;
    glm::mat4 mProjection;
    float mAspectRatio;
    

    // View
    glm::mat4 mView;


    // movement
    glm::vec3 mPosition;
    const float mSpeed = 4.5f; // pixels per second along any axis
 

    // Camera Rotations
    float mPitch;



    void CalculateView();
    void CalculateProjection();
public:
    Camera();
    Camera(ProjectionType type, glm::vec3 position,  float windowAspectRatio);
    void Update();
    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();
    void MoveCameraRight(float dt);
    void MoveCameraLeft(float dt);
    void MoveCameraForward(float dt);
    void MoveCameraBackward(float dt);
    void MoveCameraUp(float dt);
    void MoveCameraDown(float dt);
    void PitchCamera();
    ~Camera() = default;
};