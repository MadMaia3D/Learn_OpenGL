#ifndef LIGHT_H
#define LIGHT_H


#include <glm/glm.hpp>


#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2


typedef struct {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float intensity;
    float inner_cutoff_angle;
    float outer_cutoff_angle;
    int type;
} Light;


#endif