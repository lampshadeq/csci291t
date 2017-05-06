#include "LevelLoader.h"

/*******************************************************************************
*
*******************************************************************************/
LevelLoader::LevelLoader()
: levelSizeX(0), levelSizeY(0) {
  // Initialize the models
  obstacles['D'].init("images/tiles/dirt.png");
  obstacles['G'].init("images/tiles/grass.png");
  obstacles['P'].init("images/tiles/pavement.png");
}

/*******************************************************************************
*
*******************************************************************************/
LevelLoader::~LevelLoader() {

}

/*******************************************************************************
*
*******************************************************************************/
void LevelLoader::draw() {
  // For every obstacle on the level
  for (int i = 0; i < levelSizeY; i++) {
    for (int j = 0 ; j < levelSizeX; j++) {
      // Draw the obstacle
      glPushMatrix();
        level[i][j]->setTranslateX(-7.0 + j * 1.0);
        level[i][j]->setTranslateY(-3.0 + i * 1.0);
        level[i][j]->draw();
      glPopMatrix();
    }
  }
}

/*******************************************************************************
*
*******************************************************************************/
float LevelLoader::getStartX() {
  float x = 0.f;

  // For every obstacle on the level
  for (int i = 0; i < levelSizeY; i++) {
    for (int j = 0 ; j < levelSizeX; j++) {
      // Calculate the start coordinate's x translation
      if (i == startCoord[0] && j == startCoord[1]) {
        x = -7.f + j * 1.f;
      }
    }
  }

  return x;
}

/*******************************************************************************
*
*******************************************************************************/
float LevelLoader::getStartY() {
  float y = 0.f;

  // For every obstacle on the level
  for (int i = 0; i < levelSizeY; i++) {
    for (int j = 0 ; j < levelSizeX; j++) {
      // Calculate the start coordinate's x translation
      if (i == startCoord[0] && j == startCoord[1]) {
        y = -3.f + i * 1.f;
      }
    }
  }

  return y;
}

/*******************************************************************************
*
*******************************************************************************/
void LevelLoader::load(char* filename) {
  ifstream     ifs;
  int          line;
  string       str;
  stringstream ss;

  // Open the file
  ifs.open(filename);

  // Parse the level size
  ifs >> str >> str;
  ss  << str;
  ss  >> levelSizeX;
  ss.clear();
  ifs >> str;
  ss  << str;
  ss  >> levelSizeY;

  // Initialize the vector
  level.resize(levelSizeY);
  for (unsigned int i = 0; i < levelSizeY; i++) {
    level[i].resize(levelSizeX);
  }

  // Parse the starting coordinate
  ifs >> str >> str;
  ss.clear();
  ss  << str;
  ss  >> startCoord[0];
  ifs >> str;
  ss.clear();
  ss  << str;
  ss  >> startCoord[1];

  // Parse the ending coordinate
  ifs >> str >> str;
  ss.clear();
  ss  << str;
  ss  >> endCoord[0];
  ifs >> str;
  ss.clear();
  ss  << str;
  ss  >> endCoord[1];

  // Parse the map
  line = 0;
  getline(ifs, str);
  getline(ifs, str);
  while (getline(ifs, str)) {
    // For each character in the line, add the appropriate obstacle
    for (unsigned int i = 0; i < str.size(); i++) {
      level[line][i] = &obstacles[str[i]];
    }

    // Update the line count
    line++;
    if (line == levelSizeY) {
      break;
    }
  }

  // Close the file
  ifs.close();
}
