#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;

out vec3 outColor;
uniform float offset;

void main() {
    gl_Position = vec4(position.x+offset,position.yz,1.0f);
    outColor = vertexColor;
}