#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SOIL.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

class TextureLoader {
  public:
    TextureLoader();
    ~TextureLoader();

    void bindTexture(const char*);
    void binder();

  private:
    GLuint         tex;
    int            width, height;
    unsigned char* image;
};

#endif
