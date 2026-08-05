#ifndef DEBBUGING_H
#define DEBBUGING_H

#include "imgui/unity_build_imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "engine.h"


void ImguiDebug(SceneData *scene) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Debug");

    ImGui::DragFloat("Time Scale", &scene->time_scale, 0.025f, 0.0f, 10.0f);
    ImGui::DragFloat("Camera Speed", &scene->camera.speed, 0.025f, 0.1f, 50.0f);

    ImGui::Separator();
    static int selected_light = 0;
    const char *light_numbers[] = { "Light 1", "Light 2", "Light 3", "Light 4" };

    ImGui::Combo("Config", &selected_light, light_numbers, 4);
    Light *light = &scene->lights[selected_light];
    const char *light_types[] = { "Point Light", "Directional", "Spotlight" };
    ImGui::Combo("Light Type", &light->type, light_types, sizeof(light_types) / sizeof(light_types[0]));

    if (light->type != LIGHT_TYPE_DIRECTIONAL) {
        ImGui::DragFloat3("Light Position", glm::value_ptr(light->position), 0.1f);
    }

    if (light->type != LIGHT_TYPE_POINT) {
        ImGui::DragFloat3("Light Direction", glm::value_ptr(light->direction), 0.01f, -1.0f, 1.0f);
    }

    ImGui::DragFloat("Light Intensity", &light->intensity, 0.1f, 0.0f, 10000.0f);
    ImGui::ColorEdit3("Light Color", glm::value_ptr(light->color));

    if (light->type == LIGHT_TYPE_SPOT) {
        ImGui::DragFloat("Light Inner Cutoff", &light->inner_cutoff_angle, 0.1f, 0.0f, light->outer_cutoff_angle - 0.01f);
        ImGui::DragFloat("Light Outer Cutoff", &light->outer_cutoff_angle, 0.1f, light->inner_cutoff_angle + 0.01f, 90.0f);
    }

    ImGui::Checkbox("Attach to Camera", &light->attach_to_camera);
    ImGui::Separator();

    ImGui::DragFloat("Material Power", &scene->material.shininess, 0.25f, 1.0f, 300.0f);
    ImGui::ColorEdit3("Ambient", glm::value_ptr(scene->material.ambient));
    scene->bg_color = glm::vec4(scene->material.ambient, 1.0f);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


#endif