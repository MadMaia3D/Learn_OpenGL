#ifndef ENGINE_H
#define ENGINE_H


#include "mouse.h"
#include "camera.h"
#include "light.h"
#include "material.h"
#include "shader_utils.h"
#include "texture_utils.h"


typedef struct {
    glm::vec4 bg_color;
    Camera3D camera;
    Mouse mouse;

    Light light;
    Material material;

    unsigned int VBO_cube;
    unsigned int VAO_crate;
    unsigned int VAO_light;

    Program crate_program;
    Program light_program;

    Texture2D tex0;
    Texture2D tex1;
} SceneData;



void SetupScene(GLFWwindow *window, SceneData *scene);
void ProcessInput(GLFWwindow *window, SceneData *scene, float delta_time);
void RenderSceneFrame(GLFWwindow *window, SceneData *scene, float delta_time);

#endif
