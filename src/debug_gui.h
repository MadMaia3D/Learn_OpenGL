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
    ImGui::DragFloat("Camera Speed", &scene->camera.speed, 5.0f, 0.1f, 50.0f);
    ImGui::Separator();
    ImGui::DragFloat("Light Intensity", &scene->light.intensity, 0.1f, 0.0f, 10000.0f);
    ImGui::DragFloat3("Light Position", glm::value_ptr(scene->light.position), 0.1f);
    ImGui::ColorEdit3("Light Color", glm::value_ptr(scene->light.color));
    ImGui::Separator();
    ImGui::ColorEdit3("Material Ambient", glm::value_ptr(scene->material.ambient));
    // ImGui::ColorEdit3("Material Diffuse", glm::value_ptr(scene->material.diffuse));
    // ImGui::ColorEdit3("Material Specular", glm::value_ptr(scene->material.specular));
    ImGui::DragFloat("Material Power", &scene->material.shininess, 0.1f, 1.0f, 300.0f);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


#endif