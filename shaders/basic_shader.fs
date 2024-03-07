#version 410 core


in vec2 v_TextureUVs;
in vec3 v_WorldVertex;
in vec3 v_WorldNormal;

out vec4 f_Color;

void main() {
    f_Color = vec4(0.5, 0.0, 0.0, 1.0);
}
