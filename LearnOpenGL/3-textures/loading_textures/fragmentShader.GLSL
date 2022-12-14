#version 330 core

in vec3 ourColor;
in vec2 texCoordinate;

out vec4 fragColor;

uniform sampler2D ourTexture;

void main() {
    fragColor = texture(ourTexture,texCoordinate);
}