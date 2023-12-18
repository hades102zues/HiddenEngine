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
    glm::vec3 mPosition;
    glm::vec3 mLookingAt;

    // Camera Rotations
    float mPitch;
    float mYaw ;


    void CalculateView();
    void CalculateProjection();
public:
    Camera();
    Camera(ProjectionType type, glm::vec3 position, glm::vec3 at, float windowAspectRatio);
    void Update();
    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();
    ~Camera() = default;
};