#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <Parallax.h>
#include <LevelLoader.h>
#include <Player.h>
#include <Sound.h>
#include <string>

using namespace std;

class GLScene {
  public:
    GLScene();
    ~GLScene();

    GLint  draw();
    GLint  init();
    GLvoid resizeScene(GLsizei, GLsizei);
    int    windowMsg(HWND, UINT, WPARAM, LPARAM);

  private:
    bool checkCollision(Model*, Model*);
    bool checkCollision(Player*, LevelLoader*);
    bool checkCollision(Player*, Model*);
    bool collision(float, float, float, float, float, float, float, float);
    void printText(float, float, float, string);

    bool         pauseFlag;
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
