#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H


#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

#include "light.h"
#include "material.h"


typedef struct Program {
    unsigned int id;
} Program;


bool CreateAndCompileShader(GLenum type, unsigned int *shader_id, const char *path) {
    // Open shader file
    FILE *file;
    file = fopen(path, "r");

    if (file == NULL) {
        printf("File couldn't be opened: %s\n", path);
        fclose(file);
        return false;
    }

    // Calculate file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Create buffer to receive the file contents
    char *buffer = (char *)malloc(file_size + 1);

    if (buffer == NULL) {
        printf("Memory allocation failed for shader: %s", path);
        fclose(file);
        return false;
    }

    // Read Contents from file to the buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';

    // Create and Compile Shader
    unsigned int new_shader;
    new_shader = glCreateShader(type);
    glShaderSource(new_shader, 1, &buffer, NULL);
    glCompileShader(new_shader);

    // Free resources
    fclose(file);
    free(buffer);

    // Check for erros
    int success;
    char info_log[512];
    glGetShaderiv(new_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(new_shader, 511, NULL, info_log);
        printf("ERROR: SHADER COMPILATION FAILED: %s\n%s\n", path, info_log);
        return false;
    }

    *shader_id = new_shader;
    return true;
}


bool CreateShaderProgram(Program *p, const char *vertex_shader_path, const char *fragment_shader_path) {
    unsigned int vertex_shader;
    CreateAndCompileShader(GL_VERTEX_SHADER, &vertex_shader, vertex_shader_path);

    unsigned int fragment_shader;
    CreateAndCompileShader(GL_FRAGMENT_SHADER, &fragment_shader, fragment_shader_path);

    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);
    int success;
    char info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 511, NULL, info_log);
        printf("ERROR: PROGRAM LINK FAILED\n%s\n", info_log);
        return false;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    p->id = shader_program;

    return true;
}


void UseProgram(Program p) {
    glUseProgram(p.id);
}


void SetProgramUniformInt(const Program *p, const char *uniform_name, int value) {
    glUseProgram(p->id);
    int uniform_location = glGetUniformLocation(p->id, uniform_name);
    glUniform1i(uniform_location, value);
}

void SetProgramUniformFloat(const Program *p, const char *uniform_name, float value) {
    glUseProgram(p->id);
    int uniform_location = glGetUniformLocation(p->id, uniform_name);
    glUniform1f(uniform_location, value);
}


void SetProgramUniformVec3(const Program *p, const char *uniform_name, const glm::vec3 *vector) {
    glUseProgram(p->id);
    int uniform_location = glGetUniformLocation(p->id, uniform_name);
    glUniform3fv(uniform_location, 1, glm::value_ptr(*vector));
}


void SetProgramUniformMat4(const Program *p, const char *uniform_name, const glm::mat4 *matrix) {
    glUseProgram(p->id);
    int uniform_location = glGetUniformLocation(p->id, uniform_name);
    glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(*matrix));
}


void SetProgramUniformMaterial(const Program *p, const Material *mat) {
    SetProgramUniformVec3(p, "material.ambient", &mat->ambient);
    SetProgramUniformVec3(p, "material.diffuse", &mat->diffuse);
    SetProgramUniformVec3(p, "material.specular", &mat->specular);
    SetProgramUniformFloat(p, "material.shininess", mat->shininess);
}


void SetProgramUniformLight(const Program *p, const Light *light) {
    SetProgramUniformVec3(p, "light.position", &light->position);
    SetProgramUniformFloat(p, "light.intensity", light->intensity);
    SetProgramUniformVec3(p, "light.color", &light->color);
}


#endif