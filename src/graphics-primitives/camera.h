#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>


enum class ProjectionType {
    PERSPECTIVE = 0,
    ORTHOGRAPHIC = 1
};

class Camera {
private:

    // matrix
    glm::mat4 mProjection;
    glm::mat4 mView;

    // origin and 2/3 basis vectors for coordinate system
    glm::vec3 mPosition;
    glm::vec3 mDirection;
    glm::vec3 mUp;

    // Camera Rotations
    float mPitch;
    float mYaw ;

    // Projection Type
    ProjectionType mType;
public:
    Camera(ProjectionType type, glm::vec3 position, glm::vec3 direction, glm::vec3 up, float pitch, float yaw);
    glm::mat4 Matrix();
    ~Camera() = default;
};