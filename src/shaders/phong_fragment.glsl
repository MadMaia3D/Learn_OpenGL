#version 330 core


struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};


#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2


struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float outer_cutoff;
    float inner_cutoff;
    int type;
};


uniform vec3 camera_position;
uniform Material material;
uniform Light light;


in vec3 position;
in vec2 tex_coord;
in vec3 normal;

out vec4 FragColor;


float CalculateAttenuation(Light light, float quadratic, float linear, float constant) ;
float Get_Point_Light_Diffuse_Contribution(Light light);
float Get_Point_Light_Specular_Contribution(Light light);
float Get_Directional_Light_Diffuse_Contribution(Light light);
float Get_Directional_Light_Specular_Contribution(Light light);
float Get_Spotlight_Diffuse_Contribution(Light light);


// ------------------------ MAIN ------------------------ //
void main(void) {
    vec4 diffuse_color = texture2D(material.diffuse, tex_coord);
    vec4 specular_color = texture2D(material.specular, tex_coord);
    vec3 ambient = material.ambient * diffuse_color.rgb;

    vec3 final_color = ambient;

    vec3 base_diffuse = diffuse_color.rgb * light.color * light.intensity;
    vec3 base_specular = specular_color.rgb * light.intensity;

    float attenuation = 0.0f;
    float diffuse_contribution = 0.0f;
    float specular_contribution = 0.0f;

    if (light.type == LIGHT_TYPE_POINT) {
        diffuse_contribution = Get_Point_Light_Diffuse_Contribution(light);
        specular_contribution = Get_Point_Light_Specular_Contribution(light);
        attenuation = CalculateAttenuation(light, 0.0f, 0.5f, 0.5f);
    } else if (light.type == LIGHT_TYPE_DIRECTIONAL) {
        diffuse_contribution = Get_Directional_Light_Diffuse_Contribution(light);
        specular_contribution = Get_Directional_Light_Specular_Contribution(light);
        attenuation = 1.0f;
    } else if (light.type == LIGHT_TYPE_SPOT) {
        diffuse_contribution = Get_Spotlight_Diffuse_Contribution(light);
        specular_contribution = Get_Point_Light_Specular_Contribution(light) * diffuse_contribution;
        attenuation = CalculateAttenuation(light, 0.0f, 0.5f, 0.5f);
    }
        final_color += base_diffuse * diffuse_contribution * attenuation;
        final_color += base_specular * specular_contribution * attenuation;

    FragColor = vec4(final_color, 1.0f);
}


// ------------------------ POINT LIGHT ------------------------ //
float CalculateAttenuation(Light light, float quadratic, float linear, float constant) {
    float distance_to_light = length(light.position - position);
    float quadratic_attenuation = quadratic * distance_to_light * distance_to_light;
    float linear_attenuation = linear * distance_to_light;
    float constant_attenuation = constant;
    float distance_attenuation = quadratic_attenuation + linear_attenuation + constant_attenuation;
    return 1.0f / max(distance_attenuation, 0.01f);
}


// ------------------------ POINT LIGHT ------------------------ //
float Get_Point_Light_Diffuse_Contribution(Light light) {
    vec3 light_dir = normalize(light.position - position);
    float light_direction_contribution = max( 0.0f, dot(normal, light_dir));
    return light_direction_contribution;
}


float Get_Point_Light_Specular_Contribution(Light light) {
    vec3 light_dir = normalize(light.position - position);
    vec3 reflected_ray = reflect(-light_dir, normal);
    vec3 view_direction = normalize(camera_position - position);
    float highlight_dot = max(0.0f, dot(reflected_ray, view_direction));

    float highlight_occlusion = ceil(dot(light_dir, normal));    // backfacing faces should never have a highlight
    return pow(highlight_dot * highlight_occlusion, material.shininess);
}



// ------------------------ DIRECTIONAL LIGHT ------------------------ //
float Get_Directional_Light_Diffuse_Contribution(Light light) {
    vec3 light_dir = normalize(-light.direction);
    float light_direction_contribution = max( 0.0f, dot(normal, light_dir));
    return light_direction_contribution;
}


float Get_Directional_Light_Specular_Contribution(Light light) {
    vec3 light_dir = normalize(-light.direction);
    vec3 reflected_ray = reflect(-light_dir, normal);
    vec3 view_direction = normalize(camera_position - position);
    float highlight_dot = max(0.0f, dot(reflected_ray, view_direction));

    float highlight_occlusion = ceil(dot(light_dir, normal));    // backfacing faces should never have a highlight
    return pow(highlight_dot * highlight_occlusion, material.shininess);
}


// ------------------------ SPOTLIGHT ------------------------ //
float Get_Spotlight_Diffuse_Contribution(Light light) {
    vec3 light_dir = normalize(light.position - position);
    float light_direction_contribution = max( 0.0f, dot(normal, light_dir));

    float spotlight_dot = dot(light_dir, -normalize(light.direction));
    float spot_contribution = smoothstep(light.outer_cutoff, light.inner_cutoff, spotlight_dot);

    return spot_contribution * light_direction_contribution;
}
