#include "GLScene.h"

/*******************************************************************************
*
*******************************************************************************/
GLScene::GLScene() {
  init();

  // Setup the sound
  sound = new Sound();
  sound->init();
  sound->playBackground();
}

/*******************************************************************************
*
*******************************************************************************/
GLScene::~GLScene() {
  delete light;
  delete inputs;
  delete levelLoader;
  delete player;
  delete sound;
}

/*******************************************************************************
*
*******************************************************************************/
bool GLScene::checkCollision(Model* m1, Model* m2) {
  return collision(m1->getTranslateX(), m1->getTranslateY(), 0.7f, 0.7f,
                   m2->getTranslateX(), m2->getTranslateY(), 0.7f, 0.7f);
}

/*******************************************************************************
*
*******************************************************************************/
bool GLScene::checkCollision(Player* p, Model* m) {
  return collision(p->getX(), p->getY(), 0.7f, 0.7f, m->getTranslateX(),
                   m->getTranslateY(), 0.7f, 0.7f);
}

/*******************************************************************************
*
*******************************************************************************/
bool GLScene::collision(float x1, float y1, float w1, float h1, float x2,
                        float y2, float w2, float h2) {
  return (x1 < x2 + w2) && (x1 + w1 > x2) && (y1 < y2 + h2) && (y1 + h1 > y2);
}

/*******************************************************************************
*
*******************************************************************************/
GLint GLScene::draw() {
  unsigned int    i;
  vector<Model*>* v;

  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // Check for collision between player and cheeses
  v = levelLoader->getCheeses();
  for (i = 0; i < v->size(); i++) {
    if (checkCollision(player, v->at(i))) {
      delete v->at(i);
      v->erase(v->begin() + i);
      break;
    }
  }

  // Check for collision between player and bags
  v = levelLoader->getBags();
  for (i = 0; i < v->size(); i++) {
    if (checkCollision(player, v->at(i))) {
      // game over
    }
  }

  // Check for collision between projectiles nad bags

  // Draw the level
  glPushMatrix();
    levelLoader->draw();
  glPopMatrix();

  // Draw the player
  glPushMatrix();
    player->action(player->getActionTrigger(), levelLoader);
  glPopMatrix();

  // Draw the cheeses
  v = levelLoader->getCheeses();
  for (i = 0; i < v->size(); i++) {
    glPushMatrix();
      v->at(i)->draw();
    glPopMatrix();
  }

  // Draw the bags
  v = levelLoader->getBags();
  for (i = 0; i < v->size(); i++) {
    glPushMatrix();
      v->at(i)->draw();
    glPopMatrix();
  }

  // Success
  return 1;
}

/*******************************************************************************
*
*******************************************************************************/
GLint GLScene::init() {
  // Setup OpenGL
  glShadeModel(GL_SMOOTH);
  glClearColor(0.f, 0.f, 0.f, 0.5f);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  // Retrieve the system dimensions
  width  = GetSystemMetrics(SM_CXSCREEN);
  height = GetSystemMetrics(SM_CYSCREEN);

  // Setup the lighting
  light = new GLLight();
  light->setupLight(GL_LIGHT0);

  // Setup the inputs
  inputs = new Inputs();

  // Setup the level loader
  levelLoader = new LevelLoader();
  levelLoader->load("levels/level1");

  // Setup the player
  player = new Player();
  player->init();
  player->setX(levelLoader->getStartX() + 0.2f);
  player->setY(levelLoader->getStartY());

  // Success
  return 1;
}

/*******************************************************************************
*
*******************************************************************************/
GLvoid GLScene::resizeScene(GLsizei w, GLsizei h) {
  GLdouble aspectRatio;

  // Calculate the aspect ratio
  aspectRatio = (GLdouble) w / (GLdouble) h;

  // Update the scene's dimensions
  width  = w;
  height = h;

  // Update OpenGL's settings
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, aspectRatio, 0.1, 100.0);

  // Reset to the correct viewing
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*******************************************************************************
*
*******************************************************************************/
int GLScene::windowMsg(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
  // Pass the WPARAM to the inputs
  inputs->setWP(wp);

  switch (msg) {
    // Key is being held
    case WM_KEYDOWN:
      inputs->keyDown(player);
      break;

    // Key is being released
    case WM_KEYUP:
      inputs->keyUp(player);
      break;

    // Mouse button is being held
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
      //inputs->mouseDown(model, LOWORD(lp), HIWORD(lp));
      break;

    // Mouse button is being released
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
      //inputs->mouseUp();
      break;

    // Mouse is moving
    case WM_MOUSEMOVE:
      //inputs->mouseMove(model, LOWORD(lp), HIWORD(lp));
      break;

    // Mouse wheel is being used
    case WM_MOUSEWHEEL:
      //inputs->mouseWheel(model, (double) GET_WHEEL_DELTA_WPARAM(wp));
      break;

    // Screen has been resized
    case WM_SIZE:
      resizeScene(LOWORD(lp), HIWORD(lp));
      break;
  }

  // Done
  return 0;
}
