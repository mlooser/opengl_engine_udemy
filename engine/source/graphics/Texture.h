#pragma once

#include <GL/glew.h>

namespace  eng {
    class Texture {
    public:
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