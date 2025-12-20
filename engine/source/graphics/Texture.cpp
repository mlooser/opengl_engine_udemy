//
// Created by Marcin Lusa on 20/12/2025.
//

#include "Texture.h"

#include "io/FileSystem.h"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>

std::shared_ptr<eng::Texture> eng::Texture::LoadTexture(FileSystem& fileSystem, const std::string &fileName) {
    int width, height, channels;

    auto fullPath = fileSystem.GetAssetsFolder() / fileName;

    if (!std::filesystem::exists(fullPath)) {
        std::cout << "[Texture] File not found: " << fullPath << std::endl;
        //TODO ML exceptions
        return nullptr;
    }

    unsigned char* data = stbi_load(fullPath.string().c_str(), &width, &height, &channels, 0);

    if (!data) {
        std::cout << "[Texture] Failed to load texture: " << fullPath << std::endl;
        //TODO ML exceptions
        return nullptr;
    }

    auto texture = std::make_shared<eng::Texture>(width, height, channels, data);
    stbi_image_free(data);
    return texture;
}

void eng::Texture::InitializeTexture(int width, int height, unsigned char *data) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

eng::Texture::Texture(int width, int height, int numberOfChannels, unsigned char *data)
    :width(width), height(height), numberOfChannels(numberOfChannels) {
    InitializeTexture(width, height, data);
}

eng::Texture::~Texture() {
    if (textureId) {
        glDeleteTextures(1, &textureId);
    }
}

GLuint eng::Texture::GetId() const {
    return textureId;
}
