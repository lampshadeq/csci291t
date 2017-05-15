#include "Player.h"

/*******************************************************************************
*
*******************************************************************************/
Player::Player() {

}

/*******************************************************************************
*
*******************************************************************************/
Player::~Player() {
  delete timer;
}

/*******************************************************************************
*
*******************************************************************************/
void Player::action(int a, LevelLoader* levelLoader) {
  char  tileType;
  float movement  = 0.1f;
  int   timerTick = 80;

  glTranslatef(x, -y, -8.f);

  switch (a) {
    // Stand
    case 0:
      if (previousTrigger == 1) {
        north[0].binder();
      }
      else if (previousTrigger == 2) {
        south[0].binder();
      }
      else if (previousTrigger == 3) {
        east[0].binder();
      }
      else {
        west[0].binder();
      }
      break;

    // North
    case 1:
      tileType = getTileForCoordinate(levelLoader, x, y - movement - 0.6f);

      if (tileType == 'G' || tileType == 'D') {
        movement = 0.f;
      }

      if (timer->getTicks() > timerTick) {
        northFrame++;
        timer->reset();
        y -= movement;
      }

      previousTrigger = 1;
      northFrame      = northFrame % 3;
      north[northFrame].binder();

      break;

    // South
    case 2:
      tileType = getTileForCoordinate(levelLoader, x, y + movement);

      if (tileType == 'G' || tileType == 'D') {
        movement = 0.f;
      }

      if (timer->getTicks() > timerTick) {
        southFrame++;
        timer->reset();
        y += movement;
      }

      previousTrigger = 2;
      southFrame      = southFrame % 3;
      south[southFrame].binder();

      break;

    // East
    case 3:
      tileType = getTileForCoordinate(levelLoader, x + movement + 0.6f, y);

      if (tileType == 'G' || tileType == 'D') {
        movement = 0.f;
      }

      if (timer->getTicks() > timerTick) {
        eastFrame++;
        timer->reset();
        x += movement;
      }

      previousTrigger = 3;
      eastFrame       = eastFrame % 3;
      east[eastFrame].binder();

      break;

    // West
    case 4:
      tileType = getTileForCoordinate(levelLoader, x - movement, y);

      if (tileType == 'G' || tileType == 'D') {
        movement = 0.f;
      }

      if (timer->getTicks() > timerTick) {
        westFrame++;
        timer->reset();
        x -= movement;
      }

      previousTrigger = 4;
      westFrame       = westFrame % 3;
      west[westFrame].binder();

      break;
  }

  draw();
}

/*******************************************************************************
*
*******************************************************************************/
void Player::addProjectile(Model* m) {
  projectiles.push_back(m);
  m->setActive(false);
}

/*******************************************************************************
*
*******************************************************************************/
void Player::draw() {
  // Scale the player
  glScalef(playerSize[0], playerSize[1], playerSize[2]);

  // Draw the player quad
  glBegin(GL_QUADS);
    glTexCoord2f(0.f, 1.f);
    glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);

    glTexCoord2f(1.f, 1.f);
    glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);

    glTexCoord2f(1.f, 0.f);
    glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);

    glTexCoord2f(0.f, 0.f);
    glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
  glEnd();
}

/*******************************************************************************
*
*******************************************************************************/
int Player::getActionTrigger() {
  return actionTrigger;
}

/*******************************************************************************
*
*******************************************************************************/
vector<Model*>* Player::getProjectiles() {
  return &projectiles;
}

/*******************************************************************************
*
*******************************************************************************/
char Player::getTileForCoordinate(LevelLoader* l, float x, float y) {
  int xIdx = floor(x) + 7;
  int yIdx = floor(y) + 4;

  if (xIdx < 0 || yIdx < 0 || xIdx > l->getLevelSizeX() - 1 ||
      yIdx > l->getLevelSizeY() - 1) {
    return 'G';
  }

  return l->getLevel()[yIdx][xIdx]->getTileType();
}

/*******************************************************************************
*
*******************************************************************************/
float Player::getX() {
  return x;
}

/*******************************************************************************
*
*******************************************************************************/
float Player::getY() {
  return y;
}

/*******************************************************************************
*
*******************************************************************************/
void Player::init() {
  // Initialize the variables
  actionTrigger   = 0;
  previousTrigger = 1;
  northFrame      = 0;
  southFrame      = 0;
  eastFrame       = 0;
  westFrame       = 0;
  x               = 0.f;
  y               = 0.f;

  // Start the timer
  timer = new Timer();
  timer->start();

  // Enable blending for the textures
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Load the textures
  stringstream ss;
  for (int i = 0; i < 3; i++) {
    // North
    ss.str("");
    ss << "images/chicken/north_" << i << ".png";
    north[i].bindTexture(ss.str().c_str());

    // South
    ss.str("");
    ss << "images/chicken/south_" << i << ".png";
    south[i].bindTexture(ss.str().c_str());

    // East
    ss.str("");
    ss << "images/chicken/east_" << i << ".png";
    east[i].bindTexture(ss.str().c_str());

    // West
    ss.str("");
    ss << "images/chicken/west_" << i << ".png";
    west[i].bindTexture(ss.str().c_str());
  }
}

/*******************************************************************************
*
*******************************************************************************/
void Player::launchProjectile(Sound* sound) {
  bool         d;
  float        tx, ty, vel;
  unsigned int i, j;

  if (projectiles.empty()) {
    return;
  }

  // Find the next available projectile
  j = projectiles.size();
  for (i = 0; i < projectiles.size(); i++) {
    if (!projectiles[i]->isActive()) {
      j = i;
      break;
    }
  }

  // Initialize the projectile
  if (j != projectiles.size()) {
    switch (previousTrigger) {
      // North
      case 1:
        tx  = x;
        ty  = y - 1.f;
        vel = -1.f;
        d   = false;
        break;

      // South
      case 2:
        tx  = x;
        ty  = y + 1.f;
        vel = 1.f;
        d   = false;
        break;

      // East
      case 3:
        tx  = x + 1.f;
        ty  = y;
        vel = 1.f;
        d   = true;
        break;

      // West
      case 4:
        tx  = x - 1.f;
        ty  = y;
        vel = -1.f;
        d   = true;
        break;
    }

    projectiles[j]->setTranslateX(tx);
    projectiles[j]->setTranslateY(ty);
    projectiles[j]->setActive(true);
    projectiles[j]->setVelocity(vel);
    projectiles[j]->setDirection(d);
  }

  // Make projectile sound
  sound->playThrowCheese();
}

/*******************************************************************************
*
*******************************************************************************/
void Player::setActionTrigger(int a) {
  actionTrigger = a;
}

/*******************************************************************************
*
*******************************************************************************/
void Player::setX(float xx) {
  x = xx;
}

/*******************************************************************************
*
*******************************************************************************/
void Player::setY(float yy) {
  y = yy;
}
