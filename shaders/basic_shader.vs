#version 410 core


layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTextureCoords;
layout(location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main () {
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}