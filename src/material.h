#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "texture_utils.h"


typedef struct {
    glm::vec3 ambient;
    Texture2D diffuse;
    Texture2D specular;
    float shininess;
} Material;


#endif