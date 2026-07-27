#ifndef WINDOW_H
#define WINDOW_H


#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void glfw_error_callback(int error, const char *description) {
    printf("GLFW Error %d: %s\n", error, description);
}


void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}


void ProcessWindowInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


int CreateWindow(GLFWwindow **window, const char *title, int width, int height) {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(*window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        glfwTerminate();
        return 0;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(*window, FramebufferSizeCallback);

    return 1;
}


#endif