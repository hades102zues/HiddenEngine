#version 410 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTextureCoords;
layout(location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec2 v_TextureUVs;
out vec3 v_WorldVertex;
out vec3 v_WorldNormal;


void main() {
    v_TextureUVs = aTextureCoords;

    v_WorldVertex = vec3(model * vec4(aPosition, 1.0));

    mat3 NormalMatrix = mat3(transpose(inverse(model)));
    v_WorldNormal = vec3(NormalMatrix * aNormal);

    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}