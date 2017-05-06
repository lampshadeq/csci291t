#ifndef MODEL_H
#define MODEL_H

#include <cstdlib>
#include <GL/gl.h>
#include <TextureLoader.h>

class Model {
  public:
    Model();
    ~Model();

    void   draw();
    double getRotateX();
    double getRotateY();
    double getTranslateX();
    double getTranslateY();
    double getZoom();
    void   init(char*);
    void   setRotateX(double);
    void   setRotateY(double);
    void   setTranslateX(double);
    void   setTranslateY(double);
    void   setZoom(double);

  private:
    double         rotateX, rotateY, rotateZ;
    double         translateX, translateY, zoom;
    float          modelSize[3]   = {1.f, 1.f, 1.f};
    float          vertices[4][3] = {{0.f, 0.f, -1.5f}, {1.f, 0.f, -1.5f},
                                     {1.f, 1.f, -1.5f}, {0.f, 1.f, -1.5f}};
    TextureLoader* texture;
};

#endif
