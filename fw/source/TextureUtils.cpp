#include "TextureUtils.hpp"
#include <stb_image.h>
#include "fw/internal/Logging.hpp"

using namespace std;

namespace fw
{

GLuint loadTextureFromFile(const string &filename)
{
    stbi_set_flip_vertically_on_load(true);

    int width, height, components;
    unsigned char *image = stbi_load(
        filename.c_str(), &width, &height, &components, 0
    );

    if (image == nullptr)
    {
        LOG(ERROR) << "Cannot load specified texture: " << filename;
        throw string("Cannot load specified texture: " + filename);
    }

    GLenum componentsEnum;
    switch (components)
    {
    case 3:
        componentsEnum = GL_RGB;
        break;
    case 4:
        componentsEnum = GL_RGBA;
        break;
    default:
        stbi_image_free(image);
        LOG(ERROR) << "Texture \"" << filename
            << "\" components amount is not supported.";
        throw string("Components amount currently not supported.");
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, componentsEnum, width, height, 0,
        componentsEnum, GL_UNSIGNED_BYTE, image);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);

    LOG(INFO) << "Texture \"" << filename << "\" has been loaded successfully.";

    return texture;
}

}
