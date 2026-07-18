#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>




const char *vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragment_shader_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
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

    // ------------------------- Vertex Shader -------------------------
    unsigned int vertex_shader_id;
    vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader_id);
    {
        int success;
        char info_log[512];
        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex_shader_id, 511, NULL, info_log);
            printf("ERROR: VERTEX SHADER COMPILATION FAILED\n%s\n", info_log);
        }
    }
    // ------------------------- Fragment Shader -------------------------
    unsigned int fragment_shader_id;
    fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader_id);
    {
        int success;
        char info_log[512];
        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment_shader_id, 511, NULL, info_log);
            printf("ERROR: FRAGMENT SHADER COMPILATION FAILED\n%s\n", info_log);
        }
    }
    // ------------------------- Shader Program -------------------------
    unsigned int shader_program_id;
    shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vertex_shader_id);
    glAttachShader(shader_program_id, fragment_shader_id);
    glLinkProgram(shader_program_id);
    {
        int success;
        char info_log[512];
        glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_program_id, 511, NULL, info_log);
            printf("ERROR: PROGRAM LINK FAILED\n%s\n", info_log);
        }
    }
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    // ------------------------- VAO (Vertex Array Object -------------------------
    // holds the current configuration for the mesh and shader
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // ------------------------- VBO (Vertex Buffer Object) -------------------------
    // holds vertex data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // 0. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // ------------------------- EBO (Element Buffer Object) -------------------------
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    (GL_FRONT_AND_BACK, GL_FILL);
    // ------------------------- MAIN LOOP -------------------------
    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader_program_id);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
