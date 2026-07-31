#include <memory>
#include <math.h>
#include "window.h"
#include "engine.h"
#include "debugging.h"


int main(void) {
    GLFWwindow *window;
    if (!CreateWindow(&window, "LearnOpenGL", 800, 600)) { return -1; }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    SceneData scene = {};
    SetupScene(window, &scene);

    // ------------------------- MAIN LOOP -------------------------
    glEnable(GL_DEPTH_TEST);

    float last_time = 0.0f;
    
    while (!glfwWindowShouldClose(window)) {
        ProcessWindowInput(window);
        UpdateMouse(window, &scene.mouse);

        
        glClearColor(scene.bg_color.r, scene.bg_color.g, scene.bg_color.b, scene.bg_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float time = glfwGetTime();
        float delta_time = time - last_time;
        last_time = time;
        
        RenderSceneFrame(window, &scene, delta_time);
        ImguiDebug(&scene);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

#include "imgui/unity_build_imgui.cpp"