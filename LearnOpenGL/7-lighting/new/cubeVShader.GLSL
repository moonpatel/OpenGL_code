#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 fragPos;

uniform mat4 cubeModel;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection*view*cubeModel*vec4(position,1);
    fragPos = vec3(cubeModel*vec4(position,1));
    // fragPos = position;
    Normal = normal;
}