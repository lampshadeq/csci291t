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
    char   getTileType();
    double getTranslateX();
    double getTranslateY();
    double getZoom();
    void   init(char*);
    bool   isActive();
    void   setActive(bool);
    void   setDirection(bool);
    void   setModelSize(float, float, float);
    void   setRotateX(double);
    void   setRotateY(double);
    void   setTileType(char);
    void   setTranslateX(double);
    void   setTranslateY(double);
    void   setVelocity(float);
    void   setZoom(double);

  private:
    bool           active, direction;
    char           tileType;
    double         rotateX, rotateY, rotateZ;
    double         translateX, translateY, zoom;
    float          velocity;
    float          modelSize[3]   = {1.f, 1.f, 1.f};
    float          vertices[4][3] = {{0.f, 0.f, -1.5f}, {1.f, 0.f, -1.5f},
                                     {1.f, 1.f, -1.5f}, {0.f, 1.f, -1.5f}};
    TextureLoader* texture;
};

#endif
