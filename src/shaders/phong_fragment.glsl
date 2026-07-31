#version 330 core

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct Light {
   vec3 position;
   vec3 color;
   float intensity;
};

uniform vec3 camera_position;
uniform Material material;
uniform Light light;

in vec3 position;
in vec3 normal;

out vec4 FragColor;


float CalculateDiffuseContribution(void) {
   vec3 light_dir = normalize(light.position - position);
   float light_direction_contribution = max( 0.0f, dot(normal, light_dir));

   float distance_to_light = length(light.position - position);
   float squared_distance = pow(distance_to_light, 2.0f);
   float light_distance_contribution = 1.0f / max(squared_distance, 0.1f);

   return light_distance_contribution * light_direction_contribution;
}


float CalculateHighlightContribution(void) {
   float highlight_power = material.shininess;

   vec3 light_dir = normalize(light.position - position);
   float highlight_occlusion = ceil(dot(light_dir, normal));   // backfacing faces should never have a highlight
   vec3 reflected_ray = reflect(-light_dir, normal);
   vec3 view_direction = normalize(camera_position - position);

   float highlight_dot = max(0.0f, dot(reflected_ray, view_direction));

   float distance_to_light = length(light.position - position);
   float squared_distance = pow(distance_to_light, 2.0f);
   float light_distance_contribution = 1.0f / max(squared_distance, 0.1f);

   return pow(highlight_dot * highlight_occlusion, highlight_power) * light_distance_contribution;
}


void main(void) {
   vec3 ambient = material.ambient;
   vec3 diffuse = CalculateDiffuseContribution() * material.diffuse * light.color * light.intensity;
   vec3 highlight = CalculateHighlightContribution() * material.specular * light.intensity;
 
   FragColor = vec4(ambient + diffuse + highlight, 1.0f);
}
