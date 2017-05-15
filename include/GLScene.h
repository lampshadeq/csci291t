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
    void drawGame();
    void printText(float, float, float, string);
    void drawStartMenu();
    void drawHelpMenu();
    void drawCreditsMenu();

    bool         pauseFlag;
    double       rotateX, rotateY, rotateZ;
    double       translateX, translateY, zoom;
    float        height, width;
    GLLight*     light;
    Inputs*      inputs;
    int          state, menuState;
    LevelLoader* levelLoader;
    Model        *startMenu, *dot, *helpMenu, *creditsMenu;
    Player*      player;
    Sound*       sound;
};

#endif
