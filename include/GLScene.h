#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <Parallax.h>
#include <LevelLoader.h>
#include <Player.h>
#include <Sound.h>

class GLScene {
  public:
    GLScene();
    ~GLScene();

    GLint  draw();
    GLint  init();
    GLvoid resizeScene(GLsizei, GLsizei);
    int    windowMsg(HWND, UINT, WPARAM, LPARAM);

  private:
    double       rotateX, rotateY, rotateZ;
    double       translateX, translateY, zoom;
    float        height, width;
    GLLight*     light;
    Inputs*      inputs;
    LevelLoader* levelLoader;
    Player*      player;
    Sound*       sound;
};

#endif
