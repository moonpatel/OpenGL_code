#version 330 core

layout (location = 0) in vec3 position;
// layout (location = 1) in vec3 vertexColor;

uniform mat4 transform;

// out vec4 color;

void main() {
    gl_Position = transform*vec4(position,1.0);
    // color = vec4(vertexColor,1.0);
}