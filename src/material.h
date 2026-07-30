#ifndef MATERIAL_H
#define MATERIAL_H


#include <glm/glm.hpp>


typedef struct {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
} Material;


#endif