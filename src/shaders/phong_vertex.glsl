#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoords;
layout (location = 2) in vec3 inNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 position;
out vec2 tex_coord;
out vec3 normal;


void main(void) {
    gl_Position = projection * view * model * vec4(inPos, 1.0);
    
    position = (model * vec4(inPos, 1.0)).xyz;
    tex_coord = inTexCoords;
    normal = normalize((model * vec4(inNormal, 0.0))).xyz;
}
