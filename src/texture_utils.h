#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include <glad/glad.h>

int LoadTexture2D(unsigned int *texture, const char *file_path, bool alpha = false, bool flip_vertical = false) {
    stbi_set_flip_vertically_on_load(flip_vertical);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file_path, &width, &height, &nrChannels, 4);

    if (!data) {
        printf("Texture could't be loaded: %s\n", file_path);
        return 0;
    }
    
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    
    GLint internal_format = alpha ? GL_RGBA: GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return 1;
}
