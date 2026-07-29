#ifndef ENGINE_H
#define ENGINE_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_utils.h"
#include "texture_utils.h"
#include "mouse.h"


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


typedef struct {
    glm::vec4 bg_color;
    Camera3D camera;
    Mouse mouse;

    glm::vec3 light_position;

    unsigned int VBO_cube;
    unsigned int VAO_crate;
    unsigned int VAO_light;

    Program crate_program;
    Program light_program;

    Texture2D tex0;
    Texture2D tex1;
} SceneData;


// ------------------------- TRANSFORM DATA -------------------------
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};


void SetupScene(GLFWwindow *window, SceneData *data) {
    // ------------------------- Vertex Data -------------------------
    float vertices[] = {
    //position            //uvs        //normals
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  -0.0f, -0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  -0.0f, -0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -0.0f, -0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -0.0f, -0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  -0.0f, -0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  -0.0f, -0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -0.0f, -0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  -0.0f, -0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  -0.0f, -0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  -0.0f, -0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  -0.0f, -0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -0.0f, -0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, -0.0f, -0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, -0.0f, -0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, -0.0f, -0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, -0.0f, -0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, -0.0f, -0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, -0.0f, -0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f, -0.0f, -0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f, -0.0f, -0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, -0.0f, -0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, -0.0f, -0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f, -0.0f, -0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f, -0.0f, -0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -0.0f, -1.0f, -0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  -0.0f, -1.0f, -0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  -0.0f, -1.0f, -0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  -0.0f, -1.0f, -0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -0.0f, -1.0f, -0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -0.0f, -1.0f, -0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  -0.0f,  1.0f, -0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -0.0f,  1.0f, -0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -0.0f,  1.0f, -0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -0.0f,  1.0f, -0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  -0.0f,  1.0f, -0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  -0.0f,  1.0f, -0.0f
    };

    // ------------------------- Program Shader -------------------------
    CreateShaderProgram(&data->crate_program, "src/shaders/phong_vertex.glsl", "src/shaders/phong_fragment.glsl");
    CreateShaderProgram(&data->light_program, "src/shaders/light_vertex.glsl", "src/shaders/light_fragment.glsl");

    // ------------------------- Creates VAO and VBO -------------------------
    glGenVertexArrays(1, &data->VAO_crate);
    glBindVertexArray(data->VAO_crate);
    
    glGenBuffers(1, &data->VBO_cube);
    glBindBuffer(GL_ARRAY_BUFFER, data->VBO_cube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // tex_coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normals attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // ------------------------- Light VAO and VBO -------------------------
    glGenVertexArrays(1, &data->VAO_light);
    glBindVertexArray(data->VAO_light);

    glBindBuffer(GL_ARRAY_BUFFER, data->VBO_cube);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // ------------------------- Texture -------------------------
    LoadTexture2D(&data->tex0, 0, "textures/crate1_diffuse.png", false, true);
    SetTexture2DWrap(&data->tex0, GL_REPEAT, GL_REPEAT);
    SetTexture2DFiltering(&data->tex0, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    LoadTexture2D(&data->tex1, 1, "textures/awesomeface.png", true, true);
    SetTexture2DWrap(&data->tex1, GL_REPEAT, GL_REPEAT);
    SetTexture2DFiltering(&data->tex1, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    SetProgramUniformInt(&data->crate_program, "texture0", 0);
    SetProgramUniformInt(&data->crate_program, "texture1", 1);

    // ------------------------- Camera -------------------------
    data->camera.position = { 0.0f, 0.0f, 3.0f };
    data->camera.target = { 0.0f, 0.0f, 0.0f };
    data->camera.fov = 90.0f;
    data->camera.near = 0.1f;
    data->camera.far = 100.0f;
    data->camera.speed = 5.0f;
    data->camera.yaw = glm::pi<float>();
    data->bg_color = { 0.2f, 0.3f, 0.4f, 1.0f };

    // ------------------------- Light -------------------------
    data->light_position = {3.0f, 2.0f, 3.0f};
}


void ProcessInput(GLFWwindow *window, SceneData *scene, float delta_time) {
    Camera3D *camera = &scene->camera;
    Mouse *mouse = &scene->mouse;
    glm::vec3 world_up(0.0f, 1.0f, 0.0f);
    glm::vec3 camera_z = glm::normalize(camera->position - camera->target);
    glm::vec3 camera_x = glm::normalize(glm::cross(world_up, camera_z));
    glm::vec3 camera_y = glm::cross(camera_z, camera_x);

    float cam_speed = scene->camera.speed;
    if (glfwGetKey(window, GLFW_KEY_W)) {
        camera->position -= camera_z * cam_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        camera->position += camera_z * cam_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        camera->position -= camera_x * cam_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        camera->position += camera_x * cam_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        camera->position.y += cam_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        camera->position.y -= cam_speed * delta_time;
    }

    if (mouse->state == MOUSE_HOLD) {
        float delta_x = mouse->last_x - mouse->x;
        camera->yaw += delta_x * 0.004f;
        float delta_y = mouse->last_y - mouse->y;
        camera->pitch += delta_y * 0.004f;
        camera->pitch = glm::clamp(camera->pitch, glm::radians(-80.0f), glm::radians(80.0f));
    }
}


void RenderSceneFrame(GLFWwindow *window, SceneData *scene, float delta_time) {
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    float time = glfwGetTime();
    
    // ------------------------- Camera -------------------------
    Camera3D *camera = &scene->camera;
    float aspect_ratio = (float)window_width / window_height;
    float fov = scene->camera.fov;
    float near = scene->camera.near;
    float far = scene->camera.far;
    
    glm::vec3 world_up(0.0f, 1.0f, 0.0f);
    
    float yaw = camera->yaw;
    float pitch = camera->pitch;
    camera->target.x = sin(yaw) * cos(pitch);
    camera->target.y = sin(pitch);
    camera->target.z = cos(yaw) * cos(pitch);
    camera->target += camera->position;
    ProcessInput(window, scene, delta_time);

    glm::vec3 camera_z = glm::normalize(camera->position - camera->target);
    glm::vec3 camera_x = glm::cross(world_up, camera_z);
    glm::vec3 camera_y = glm::cross(camera_z, camera_x);
    glm::mat4 look_at = glm::lookAt(camera->position, camera->target, glm::vec3(0.0, 1.0, 0.0));
    
    // ------------------------- Proj Matrix -------------------------
    glm::mat4 proj = glm::perspective(glm::radians(fov / 2), aspect_ratio, near, far);

    // ------------------------- Light Transformation -------------------------
    glm::vec3 light_position = glm::vec3(cos(time/2), 0.5f, sin(time/2)) * 8.0f;
    light_position.z -= 3.0f;
    
    int nCubes = sizeof(cubePositions) / sizeof(cubePositions[0]);
    
    glBindVertexArray(scene->VAO_crate);
    UseProgram(scene->crate_program);
    SetProgramUniformMat4(&scene->crate_program, "projection", &proj);
    SetProgramUniformMat4(&scene->crate_program, "view", &look_at);
    SetProgramUniformVec3(&scene->crate_program, "light_position", &light_position);
    SetProgramUniformVec3(&scene->crate_program, "camera_position", &camera->position);
    
    for (int i = 0; i < nCubes; i++) {
        // ------------------------- Transforms -------------------------
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i + time * 5.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        // ------------------------- Pass transforms to shader -------------------------
        SetProgramUniformMat4(&scene->crate_program, "model", &model);
        // ------------------------- Render Cube -------------------------
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    // ------------------------- Render Light -------------------------
    glBindVertexArray(scene->VAO_light);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light_position);
    model = glm::scale(model, glm::vec3(0.2f));
    
    UseProgram(scene->light_program);
    SetProgramUniformMat4(&scene->light_program, "model", &model);
    SetProgramUniformMat4(&scene->light_program, "view", &look_at);
    SetProgramUniformMat4(&scene->light_program, "projection", &proj);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


#endif
