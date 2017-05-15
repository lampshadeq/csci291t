#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <Player.h>
#include <Sound.h>

class Inputs {
  public:
    Inputs();
    ~Inputs();

    void mouseDown(Player*, double, double);
    void mouseMove(Player*, double, double);
    void mouseUp();
    void mouseWheel(Player*, double);
    void keyDown(int&, int&, Sound*);
    void keyDown(Player*, int&);
    void keyUp(Player*);
    void setWP(WPARAM);

  private:
    bool   mouseTranslate, mouseRotate;
    double prevMouseX, prevMouseY;
    WPARAM wp;
};

#endif
