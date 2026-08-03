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
    Light *light = &scene->light;
    ImGui::DragFloat3("Light Position", glm::value_ptr(light->position), 0.1f);
    ImGui::DragFloat3("Light Direction", glm::value_ptr(light->direction), 0.1f);
    ImGui::DragFloat("Light Intensity", &light->intensity, 0.1f, 0.0f, 10000.0f);
    ImGui::ColorEdit3("Light Color", glm::value_ptr(light->color));
    ImGui::DragFloat("Light Inner Cutoff", &light->inner_cutoff_angle, 0.1f, 0.0f, light->outer_cutoff_angle - 0.01f);
    ImGui::DragFloat("Light Outer Cutoff", &light->outer_cutoff_angle, 0.1f, light->inner_cutoff_angle + 0.01f, 90.0f);
    ImGui::Separator();
    ImGui::ColorEdit3("Material Ambient", glm::value_ptr(scene->material.ambient));
    ImGui::DragFloat("Material Power", &scene->material.shininess, 0.25f, 1.0f, 300.0f);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


#endif