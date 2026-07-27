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

    unsigned int VAO;
    unsigned int VBO;

    Program shader_program;

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
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // ------------------------- Program Shader -------------------------
    CreateShaderProgram(&data->shader_program, "src/shaders/coord_shader_vertex.glsl", "src/shaders/coord_shader_fragment.glsl");
    UseProgram(data->shader_program);

    // ------------------------- VAO (Vertex Array Object) -------------------------
    glGenVertexArrays(1, &data->VAO);
    glBindVertexArray(data->VAO);

    // ------------------------- VBO (Vertex Buffer Object) -------------------------
    glGenBuffers(1, &data->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, data->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // tex_coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ------------------------- Texture -------------------------
    LoadTexture2D(&data->tex0, 0, "textures/crate1_diffuse.png", false, true);
    SetTexture2DWrap(&data->tex0, GL_REPEAT, GL_REPEAT);
    SetTexture2DFiltering(&data->tex0, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    LoadTexture2D(&data->tex1, 1, "textures/awesomeface.png", true, true);
    SetTexture2DWrap(&data->tex1, GL_REPEAT, GL_REPEAT);
    SetTexture2DFiltering(&data->tex1, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    SetProgamUniformInt(&data->shader_program, "texture0", 0);
    SetProgamUniformInt(&data->shader_program, "texture1", 1);

    // ------------------------- Camera -------------------------
    data->camera.position = { 0.0f, 0.0f, 3.0f };
    data->camera.target = { 0.0f, 0.0f, 0.0f };
    data->camera.fov = 90.0f;
    data->camera.near = 0.1f;
    data->camera.far = 100.0f;
    data->camera.speed = 2.0f;
    data->camera.yaw = glm::pi<float>();
    data->bg_color = { 0.2f, 0.3f, 0.4f, 1.0f };
}


void ProcessInput(GLFWwindow *window, SceneData *scene, float delta_time) {
    Camera3D *camera = &scene->camera;
    Mouse *mouse = &scene->mouse;
    glm::vec3 world_up(0.0f, 1.0f, 0.0f);
    glm::vec3 camera_z = glm::normalize(camera->position - camera->target);
    glm::vec3 camera_x = glm::cross(world_up, camera_z);
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
        camera->yaw += delta_x * 0.002f;
        float delta_y = mouse->last_y - mouse->y;
        camera->pitch += delta_y * 0.002f;
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

    // ------------------------- View Matrix -------------------------
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, -scene->camera.position);
    
    // ------------------------- Proj Matrix -------------------------
    glm::mat4 proj = glm::perspective(glm::radians(fov / 2), aspect_ratio, near, far);
    SetProgamUniformMat4(&scene->shader_program, "projection", glm::value_ptr(proj));

    int nCubes = sizeof(cubePositions) / sizeof(cubePositions[0]);

    for (int i = 0; i < nCubes; i++) {
        // ------------------------- Transforms -------------------------
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i + time * 5.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        // ------------------------- Pass transforms to shader -------------------------
        SetProgamUniformMat4(&scene->shader_program, "model", glm::value_ptr(model));
        SetProgamUniformMat4(&scene->shader_program, "view", glm::value_ptr(look_at));

        // ------------------------- Render cube -------------------------
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}


#endif
