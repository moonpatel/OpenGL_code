#version 330 core

out vec4 fragmentColor;
uniform vec3 uniColor;

void main() {
    fragmentColor = vec4(uniColor,1);
}