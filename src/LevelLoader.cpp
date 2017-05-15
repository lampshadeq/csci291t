#include "LevelLoader.h"

/*******************************************************************************
*
*******************************************************************************/
LevelLoader::LevelLoader()
: levelSizeX(0), levelSizeY(0), levelNumber(0) {
  // Initialize the models
  obstacles['B'].init("images/tiles/bridge.png");
  obstacles['C'].init("images/tiles/ice_walkable.png");
  obstacles['D'].init("images/tiles/dirt.png");
  obstacles['E'].init("images/tiles/goal.png");
  obstacles['F'].init("images/tiles/forest.png");
  obstacles['G'].init("images/tiles/grass.png");
  obstacles['I'].init("images/tiles/ice.png");
  obstacles['L'].init("images/tiles/lava.png");
  obstacles['P'].init("images/tiles/pavement.png");
  obstacles['R'].init("images/tiles/dirt_walkable.png");
  obstacles['S'].init("images/tiles/swamp.png");
  obstacles['W'].init("images/tiles/water.png");
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
vector<Model*>* LevelLoader::getBags() {
  return &bags;
}

/*******************************************************************************
*
*******************************************************************************/
vector<Model*>* LevelLoader::getCheeses() {
  return &cheeses;
}

/*******************************************************************************
*
*******************************************************************************/
float LevelLoader::getEndX() {
  return -7.f + endCoord[1];
}

/*******************************************************************************
*
*******************************************************************************/
float LevelLoader::getEndY() {
  return -3.f + endCoord[0];
}

/*******************************************************************************
*
*******************************************************************************/
vector<vector<Model*> > LevelLoader::getLevel() {
  return level;
}

/*******************************************************************************
*
*******************************************************************************/
int LevelLoader::getLevelNumber() {
  return levelNumber;
}

/*******************************************************************************
*
*******************************************************************************/
int LevelLoader::getLevelSizeX() {
  return levelSizeX;
}

/*******************************************************************************
*
*******************************************************************************/
int LevelLoader::getLevelSizeY() {
  return levelSizeY;
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
  int          line, x, y;
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

  // Parse the cheese coordinates
  while (true) {
    ifs >> str;

    if (str == "endcheese") {
      break;
    }

    ifs >> str;
    ss.clear();
    ss  << str;
    ss  >> y;

    ifs >> str;
    ss.clear();
    ss  << str;
    ss  >> x;

    cheeses.push_back(new Model());
    cheeses.back()->init("images/items/moldy_cheese.png");
    cheeses.back()->setTranslateX(-7.f + x * 1.f);
    cheeses.back()->setTranslateY(-3.f + y * 1.f);
  }

  // Parse the bag coordinates
  while (true) {
    ifs >> str;

    if (str == "endbag") {
      break;
    }

    ifs >> str;
    ss.clear();
    ss  << str;
    ss  >> y;

    ifs >> str;
    ss.clear();
    ss  << str;
    ss  >> x;

    bags.push_back(new Model());
    bags.back()->init("images/items/feedbag.png");
    bags.back()->setTranslateX(-7.f + x * 1.f);
    bags.back()->setTranslateY(-3.f + y * 1.f);
  }

  // Parse the map
  line = 0;
  getline(ifs, str);
  getline(ifs, str);
  while (getline(ifs, str)) {
    // For each character in the line, add the appropriate obstacle
    for (unsigned int i = 0; i < str.size(); i++) {
      level[line][i] = &obstacles[str[i]];
      level[line][i]->setTileType(str[i]);
    }

    // Update the line count
    line++;
    if (line == levelSizeY) {
      break;
    }
  }

  // Close the file
  ifs.close();

  // Update the level number
  levelNumber++;
}
