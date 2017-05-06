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
  int   timerTick = 60;
  float movement  = 0.05f;

  glTranslatef(x, -y, -8.f);

  switch (a) {
    // Stand
    case 0:
      north[0].binder();
      break;

    // North
    case 1:
      if (timer->getTicks() > timerTick) {
        northFrame++;
        timer->reset();
        y -= movement;
      }
      northFrame = northFrame % 3;
      north[northFrame].binder();
      break;

    // South
    case 2:
      if (timer->getTicks() > timerTick) {
        southFrame++;
        timer->reset();
        y += movement;
      }
      southFrame = southFrame % 3;
      south[southFrame].binder();
      break;

    // East
    case 3:
      if (timer->getTicks() > timerTick) {
        eastFrame++;
        timer->reset();
        x += movement;
      }
      eastFrame = eastFrame % 3;
      east[eastFrame].binder();
      break;

    // West
    case 4:
      if (timer->getTicks() > timerTick) {
        westFrame++;
        timer->reset();
        x -= movement;
      }
      westFrame = westFrame % 3;
      west[westFrame].binder();
      break;
  }

  draw();
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
void Player::init() {
  // Initialize the variables
  actionTrigger = 0;
  northFrame    = 0;
  southFrame    = 0;
  eastFrame     = 0;
  westFrame     = 0;
  x             = 0.f;
  y             = 0.f;

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
int Player::getActionTrigger() {
  return actionTrigger;
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
