#version 330 core

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 light_position;

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec4 FragColor;


void main() {
   // albedo
   vec4 crate = texture(texture0, texCoord);
   vec4 face = texture(texture1, texCoord);
   vec3 albedo = mix(crate.rgb, face.rgb, vec3(face.a * 0.5f));

   // ambient light
   vec3 ambient_light_color = vec3(0.2f, 0.3f, 0.4f);
   vec3 ambient_final_color = albedo * ambient_light_color;
 
   // light direction
   vec3 direction_to_light = normalize(light_position - position);
   float light_direction_contribution = max( 0.0f, dot(normal, direction_to_light));

   // light distance
   float distance_to_light = length(light_position - position);
   float squared_distance = pow(distance_to_light, 2.0f);
   float light_distance_contribution = 1.0f / max(squared_distance, 0.1f);

   // light contribution
   float light_intensity = 30.0f;
   float light_final_contribution = light_distance_contribution * light_direction_contribution * light_intensity;
   vec3 diffuse_final_color = albedo * light_final_contribution;

   FragColor = vec4(ambient_final_color + diffuse_final_color, 1.0f);

}
