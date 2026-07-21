#include <stdio.h>
#include <memory>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_utils.h"
#include "texture_utils.h"


float vertices[] = {
    // positions           // tex_coords    // colors        
    -0.5f,  0.5f, 0.0f,    0.0f, 1.0f,      1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, 0.0f,    1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f,    1.0f, 0.0f,      1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,      0.0f, 0.0f, 1.0f,
};


unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3,
};


void glfw_error_callback(int error, const char *description) {
    printf("GLFW Error %d: %s\n", error, description);
}


void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}


void ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


int main(void) {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // ------------------------- Program Shader -------------------------

    unsigned shaderProgram;
    CreateShaderProgram(&shaderProgram, "src/shaders/color_shader_vertex.glsl", "src/shaders/color_shader_fragment.glsl");

    // ------------------------- VAO (Vertex Array Object -------------------------
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // ------------------------- VBO (Vertex Buffer Object) -------------------------
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // tex_coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // color attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // ------------------------- EBO (Element Buffer Object) -------------------------
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    (GL_FRONT_AND_BACK, GL_FILL);
    // ------------------------- TEXTURE -------------------------
    glUseProgram(shaderProgram);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glActiveTexture(GL_TEXTURE0);
    unsigned int texture0;
    LoadTexture2D(&texture0, "textures/crate1_diffuse.png", false, true);
    
    glActiveTexture(GL_TEXTURE1);
    unsigned int texture1;
    LoadTexture2D(&texture1, "textures/awesomeface.png", true, true);
    
    int sampler2D_location_0 = glGetUniformLocation(shaderProgram, "texture0");
    int sampler2D_location_1 = glGetUniformLocation(shaderProgram, "texture1");
    glUniform1i(sampler2D_location_0, 0);
    glUniform1i(sampler2D_location_1, 1);

    // ------------------------- MAIN LOOP -------------------------
    
    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);
        
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
