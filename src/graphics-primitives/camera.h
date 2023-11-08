#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>


enum class CameraType {
    PERSPECTIVE = 0,
    ORTHOGRAPHIC = 1
};

class Camera {
private:
    glm::mat4 mProjection;
    glm::mat4 mView;
    glm::vec3 mPosition;
    glm::vec3 mDirection;
    glm::vec3 mUp;
    float mPitch;
    float mYaw ;
    CameraType mType;
public:
    Camera(CameraType type, glm::vec3 position, glm::vec3 direction, glm::vec3 up, float pitch, float yaw);
    glm::mat4 Matrix();
    ~Camera() = default;
};