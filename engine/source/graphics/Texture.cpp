//
// Created by Marcin Lusa on 20/12/2025.
//

#include "Texture.h"

eng::Texture::Texture(int width, int height, int numberOfChannels, unsigned char *data)
    :width(width), height(height), numberOfChannels(numberOfChannels) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

eng::Texture::~Texture() {
    if (textureId) {
        glDeleteTextures(1, &textureId);
    }
}

GLuint eng::Texture::GetId() const {
}
