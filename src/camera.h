#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>


typedef struct {
    glm::vec3 position;
    glm::vec3 target;

    float fov;
    float near;
    float far;
    float speed;

    float yaw;
    float pitch;
} Camera3D;


#endif