#ifndef GLSCENE_H
#define GLSCENE_H

#include <ShaderLoader.h>
#include <windows.h>
#include <cstring>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <Parallax.h>
#include <LevelLoader.h>
#include <Player.h>
#include <Sound.h>
#include <string>
#include <Particles.h>
#include <Timer.h>

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
    void drawCreditsMenu();
    void drawGame();
    void drawGameOver();
    void drawHelpMenu();
    void drawLevelComplete();
    void drawPauseMenu();
    void drawStartMenu();
    void drawYouWon();
    void resetGame();

    bool          pauseFlag;
    double        rotateX, rotateY, rotateZ;
    double        translateX, translateY, zoom;
    float         height, width;
    GLLight*      light;
    Inputs*       inputs;
    int           state, menuState;
    LevelLoader*  levelLoader;
    Model         *startMenu, *dot, *helpMenu, *creditsMenu, *pauseMenu,
                  *gameOverText, *levelCompleteText, *youWonText;
    Particles*    particles;
    Player*       player;
    ShaderLoader* shaderLoader;
    Sound*        sound;
    Timer*        completeTimer;
};

#endif
