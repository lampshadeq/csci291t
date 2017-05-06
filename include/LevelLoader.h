#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <fstream>
#include <GL/gl.h>
#include <iostream>
#include <Model.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

class LevelLoader {
  public:
    LevelLoader();
    ~LevelLoader();

    void                    draw();
    vector<Model*>          getBags();
    vector<Model*>          getCheeses();
    float                   getEndX();
    float                   getEndY();
    vector<vector<Model*> > getLevel();
    int                     getLevelSizeX();
    int                     getLevelSizeY();
    float                   getStartX();
    float                   getStartY();
    void                    load(char*);

  private:
    int                        levelSizeX, levelSizeY, startCoord[2],
                               endCoord[2];
    vector<Model*>             cheeses, bags;
    vector<vector<Model*> >    level;
    unordered_map<char, Model> obstacles;
};

#endif
