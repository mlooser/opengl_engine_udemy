#pragma once

#include <memory>
#include <GL/glew.h>

namespace  eng {
    class FileSystem;

    class Texture {
    public:
        static std::shared_ptr<Texture> LoadTexture(FileSystem& fileSystem, const std::string& fileName);

        void InitializeTexture(int width, int height, unsigned char *data);

        Texture(int width, int height, int numberOfChannels, unsigned char* data);
        ~Texture();

        GLuint GetId() const;
    private:
        int width = 0;
        int height = 0;
        int numberOfChannels = 0;
        GLuint textureId = 0;
    };
}