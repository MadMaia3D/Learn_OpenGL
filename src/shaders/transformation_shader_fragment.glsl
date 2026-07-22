#version 330 core

uniform sampler2D texture0;
uniform sampler2D texture1;

in vec2 texCoord;

out vec4 FragColor;

void main() {
   vec4 crate = texture(texture0, texCoord);
   vec4 face = texture(texture1, texCoord);
   FragColor = vec4(mix(crate.rgb, face.rgb, face.a), 1.0f);
}
