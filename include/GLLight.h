#ifndef GLLIGHT_H
#define GLLIGHT_H

#include <GL/gl.h>

class GLLight {
  public:
    GLLight();
    ~GLLight();

    GLvoid setupLight(GLenum);

  private:
    GLfloat lightAmbient[4]  = {0.f, 0.f, 0.f, 1.f};
    GLfloat lightDiffuse[4]  = {1.f, 1.f, 1.f, 1.f};
    GLfloat lightSpecular[4] = {1.f, 1.f, 1.f, 1.f};
    GLfloat lightPosition[4] = {2.f, 5.f, 5.f, 0.f};

    GLfloat materialAmbient[4]  = {0.7f, 0.7f, 0.7f, 1.f};
    GLfloat materialDiffuse[4]  = {0.8f, 0.8f, 0.8f, 1.f};
    GLfloat materialSpecular[4] = {1.f, 1.f, 1.f, 1.f};
    GLfloat highShininess[1]    = {100.f};
};

#endif
