#ifndef PLAYER_H
#define PLAYER_H

#include <TextureLoader.h>
#include <Timer.h>
#include <sstream>
#include <iostream>
#include <LevelLoader.h>
#include <cmath>
#include <Model.h>
#include <vector>
#include <Sound.h>

using namespace std;

class Player {
  public:
    Player();
    ~Player();

    void            action(int, LevelLoader*);
    void            addProjectile(Model*);
    int             getActionTrigger();
    vector<Model*>* getProjectiles();
    float           getX();
    float           getY();
    void            init();
    void            launchProjectile(Sound*);
    void            setActionTrigger(int);
    void            setX(float);
    void            setY(float);

  private:
    char getTileForCoordinate(LevelLoader*, float, float);
    void draw();

    float          playerSize[3]  = {0.7f, 0.7f, 1.f};
    float          vertices[4][3] = {{0.f, 0.f, -1.5f}, {1.f, 0.f, -1.5f},
                                     {1.f, 1.f, -1.5f}, {0.f, 1.f, -1.5f}};
    float          x, y;
    int            actionTrigger, previousTrigger;
    int            northFrame, southFrame, eastFrame, westFrame;
    Timer*         timer;
    TextureLoader  north[3], south[3], east[3], west[3];
    vector<Model*> projectiles;
};

#endif
