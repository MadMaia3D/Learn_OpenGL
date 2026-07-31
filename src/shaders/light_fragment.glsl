#version 330 core

out vec4 FragColor;


uniform float light_intensity;
uniform vec3 light_color;


void main (void) {
    FragColor = vec4(light_color * light_intensity, 1.0f);
}
