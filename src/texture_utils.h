#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include <glad/glad.h>


typedef struct Texture2D {
    unsigned int id;
    int current_slot;
} Texture2D;


int LoadTexture2D(Texture2D *texture, unsigned int slot_number, const char *file_path, bool alpha = false, bool flip_vertical = false) {
    stbi_set_flip_vertically_on_load(flip_vertical);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file_path, &width, &height, &nrChannels, 4);

    if (!data) {
        printf("Texture could't be loaded: %s\n", file_path);
        return 0;
    }
    
    texture->current_slot = slot_number;
    glActiveTexture(GL_TEXTURE0 + texture->current_slot);
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    
    GLint internal_format = alpha ? GL_RGBA: GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glGenerateMipmap(GL_TEXTURE_2D);


    return 1;
}


void SetTextureToSlot(Texture2D *tex, unsigned int slot_number) {
    tex->current_slot = slot_number;
    glActiveTexture(GL_TEXTURE0 + slot_number);
    glBindTexture(GL_TEXTURE_2D, tex->id);
}


void SetTexture2DWrap(Texture2D *tex, GLint wrap_s_value, GLint wrap_t_value) {
    glActiveTexture(GL_TEXTURE0 + tex->current_slot);
    glBindTexture(GL_TEXTURE_2D, tex->id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_value);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_value);

}


void SetTexture2DFiltering(Texture2D *tex, GLint min_filter, GLint mag_filter) {
    glActiveTexture(GL_TEXTURE0 + tex->current_slot);
    glBindTexture(GL_TEXTURE_2D, tex->id);
    
    glActiveTexture(tex->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
}
