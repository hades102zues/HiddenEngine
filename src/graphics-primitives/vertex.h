#pragma once
#include <glm/glm.hpp>
struct Vertex {
    glm::vec3 Position;
    glm::vec2 TextCoords;
    glm::vec3 Normals;
    
};

enum class GlDraw { // defines how vertices will be drawn
    MESH_INDEX_DRAW = 0,
    MESH_ARRAY_DRAW
};