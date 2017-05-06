#ifndef FONT_H
#define FONT_H

#include <windows.h>
#include <GL/gl.h>
#include <cstdio>

class Font {
  public:
    Font();
    ~Font();

    void buildFont(HDC);
    void killFont();
    void printText(const char*);

  private:
    GLuint base;
};

#endif
