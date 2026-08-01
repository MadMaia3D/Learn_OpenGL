#version 330 core

struct Material {
   vec3 ambient;
   sampler2D diffuse;
   sampler2D specular;
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
in vec2 tex_coord;
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
   vec4 diffuse_color = texture2D(material.diffuse, tex_coord);
   vec4 specular_color = texture2D(material.specular, tex_coord);

   vec3 ambient = material.ambient * diffuse_color.rgb;
   vec3 diffuse = CalculateDiffuseContribution() * diffuse_color.rgb * light.color * light.intensity;
   vec3 highlight = CalculateHighlightContribution() * specular_color.rgb * light.intensity;
 
   FragColor = vec4(ambient + diffuse + highlight, 1.0f);
}
