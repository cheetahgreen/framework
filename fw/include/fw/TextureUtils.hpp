#include <glad/glad.h>
#include <string>

namespace fw
{

GLuint loadTextureFromFile(const std::string &filename);
GLuint loadTextureFromMemory(std::istream& stream);

}
