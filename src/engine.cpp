#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "engine.h"


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


void SetupScene(GLFWwindow *window, SceneData *scene) {
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
    CreateShaderProgram(&scene->crate_program, "src/shaders/phong_vertex.glsl", "src/shaders/phong_fragment.glsl");
    CreateShaderProgram(&scene->light_program, "src/shaders/light_vertex.glsl", "src/shaders/light_fragment.glsl");

    // ------------------------- Creates VAO and VBO -------------------------
    glGenVertexArrays(1, &scene->VAO_crate);
    glBindVertexArray(scene->VAO_crate);

    glGenBuffers(1, &scene->VBO_cube);
    glBindBuffer(GL_ARRAY_BUFFER, scene->VBO_cube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ------------------------- Light VAO and VBO -------------------------
    glGenVertexArrays(1, &scene->VAO_light);
    glBindVertexArray(scene->VAO_light);

    glBindBuffer(GL_ARRAY_BUFFER, scene->VBO_cube);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // ------------------------- Camera -------------------------
    scene->camera.position = { 0.0f, 0.0f, 3.0f };
    scene->camera.target = { 0.0f, 0.0f, 0.0f };
    scene->camera.fov = 90.0f;
    scene->camera.znear = 0.1f;
    scene->camera.zfar = 100.0f;
    scene->camera.speed = 5.0f;
    scene->camera.yaw = glm::pi<float>();
    scene->bg_color = { 0.2f, 0.3f, 0.4f, 1.0f };

    // ------------------------- Look -------------------------
    scene->light.position = { 3.0f, 2.0f, 3.0f };
    scene->light.intensity = 15.0f;
    scene->light.color = { 1.0f, 1.0f, 1.0f };

    scene->material.ambient = glm::vec3(0.3f, 0.3f, 0.3f) * 0.1f;
    scene->material.diffuse = { 1.0f, 0.5f, 0.3f };
    scene->material.specular = { 0.5f, 0.5f, 0.5f };
    scene->material.shininess = 50.0f;
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

    bool imgui_using_mouse = ImGui::GetIO().WantCaptureMouse;

    if (mouse->state == MOUSE_HOLD && !imgui_using_mouse) {
        float delta_x = mouse->last_x - mouse->x;
        camera->yaw += delta_x * 0.004f;
        float delta_y = mouse->last_y - mouse->y;
        camera->pitch += delta_y * 0.004f;
        camera->pitch = glm::clamp(camera->pitch, glm::radians(-80.0f), glm::radians(80.0f));
    }

    float yaw = camera->yaw;
    float pitch = camera->pitch;
    camera->target.x = sin(yaw) * cos(pitch);
    camera->target.y = sin(pitch);
    camera->target.z = cos(yaw) * cos(pitch);
    camera->target += camera->position;
}


void RenderSceneFrame(GLFWwindow *window, SceneData *scene, float delta_time) {
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    float time = glfwGetTime();

    // ------------------------- Camera -------------------------
    Camera3D *camera = &scene->camera;
    float aspect_ratio = (float)window_width / window_height;
    float fov = scene->camera.fov;
    float znear = scene->camera.znear;
    float zfar = scene->camera.zfar;

    ProcessInput(window, scene, delta_time);

    glm::mat4 view_mat = glm::lookAt(camera->position, camera->target, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 proj_mat = glm::perspective(glm::radians(fov / 2), aspect_ratio, znear, zfar);

    // ------------------------- Uniforms -------------------------
    SetProgramUniformMaterial(&scene->crate_program, &scene->material);
    SetProgramUniformLight(&scene->crate_program, &scene->light);
    // ------------------------- Cubes -------------------------

    glBindVertexArray(scene->VAO_crate);
    UseProgram(scene->crate_program);
    SetProgramUniformMat4(&scene->crate_program, "view", &view_mat);
    SetProgramUniformMat4(&scene->crate_program, "projection", &proj_mat);
    SetProgramUniformVec3(&scene->crate_program, "camera_position", &camera->position);

    int nCubes = sizeof(cubePositions) / sizeof(cubePositions[0]);
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
    model = glm::translate(model, scene->light.position);
    model = glm::scale(model, glm::vec3(0.1f));

    UseProgram(scene->light_program);
    SetProgramUniformMat4(&scene->light_program, "model", &model);
    SetProgramUniformMat4(&scene->light_program, "view", &view_mat);
    SetProgramUniformMat4(&scene->light_program, "projection", &proj_mat);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
