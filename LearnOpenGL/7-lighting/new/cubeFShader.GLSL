#version 330 core

in vec3 Normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

void main() {
    // calculate ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength*lightColor;

    //calculate diffuse lighting
    vec3 incidentVector = normalize(lightPos-fragPos);
    float diff = max(dot(incidentVector,Normal),0.0);
    vec3 diffuse = lightColor*diff;
    

    vec3 result = (ambient+diffuse)*objectColor;
    fragColor = vec4(result,1);
}