#include "GLScene.h"

/*******************************************************************************
*
*******************************************************************************/
GLScene::GLScene() {
  // Setup the sound
  sound = new Sound();
  sound->init();
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
  delete startMenu;
  delete dot;
  delete helpMenu;
  delete creditsMenu;
  delete pauseMenu;
  delete gameOverText;
  delete particles;
  delete shaderLoader;
  delete levelCompleteText;
  delete completeTimer;
  delete youWonText;
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
bool GLScene::checkCollision(Player* p, LevelLoader* l) {
  return collision(p->getX(), p->getY(), 0.7f, 0.7f, l->getEndX(), l->getEndY(),
                   1.f, 1.f);
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
  GLint status = 1;

  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  switch (state) {
    // Quit
    case -1:
      status = 0;
      break;

    // Menu
    case 0:
      drawStartMenu();
      if (!sound->isPlaying()) {
        sound->playMenu();
      }
      break;

    // Game
    case 1:
      drawGame();
      if (!sound->isPlaying()) {
        sound->playBackground();
      }
      break;

    // Help
    case 2:
      drawHelpMenu();
      break;

    // Credits
    case 3:
      drawCreditsMenu();
      break;

    // Game Paused
    case 4:
      drawGame();
      drawPauseMenu();
      break;

    // Game Over
    case 5:
      drawGame();
      drawGameOver();
      break;

    // Level Complete
    case 6:
      drawGame();
      drawLevelComplete();
      break;

    // You Won
    case 7:
      drawGame();
      drawYouWon();
      break;
  }

  // Done
  return status;
}

/*******************************************************************************
*
*******************************************************************************/
void GLScene::drawCreditsMenu() {
  // Display the credits menu
  glPushMatrix();
    creditsMenu->draw();
  glPopMatrix();
}

/*******************************************************************************
*
*******************************************************************************/
void GLScene::drawGame() {
  unsigned int    i, j;
  vector<int>     idxFlags;
  vector<Model*> *v, *w;

  // Only check for conditions during the game
  if (state == 1) {
    // Check for collision between player and cheeses
    v = levelLoader->getCheeses();
    for (i = 0; i < v->size(); i++) {
      if (checkCollision(player, v->at(i))) {
        player->addProjectile(v->at(i));
        v->erase(v->begin() + i);
        sound->playCollectCheese();
        break;
      }
    }

    // Check for collision between player and bags
    v = levelLoader->getBags();
    for (i = 0; i < v->size(); i++) {
      if (checkCollision(player, v->at(i))) {
        player->setActionTrigger(0);
        state = 5;
      }
    }

    // Check for collision between projectiles and bags
    w = player->getProjectiles();
    for (i = 0; i < w->size(); i++) {
      if (w->at(i)->isActive()) {
        for (j = 0; j < v->size(); j++) {
          if (checkCollision(w->at(i), v->at(j))) {
            delete v->at(j);
            v->erase(v->begin() + j);
            idxFlags.push_back(i);
            sound->playCheeseCollision();
            break;
          }
        }
      }
    }
    for (i = 0; i < idxFlags.size(); i++) {
      delete w->at(idxFlags[i]);
      w->erase(w->begin() + idxFlags[i]);
    }

    // Check if the player reached the end of the level
    if (checkCollision(player, levelLoader)) {
      //pauseFlag = true;
      player->setActionTrigger(0);
      state = 6;
      completeTimer->start();
    }
  }

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

  // Draw the projectiles
  v = player->getProjectiles();
  for (i = 0; i < v->size(); i++) {
    if (v->at(i)->isActive()) {
      glPushMatrix();
        v->at(i)->draw();
      glPopMatrix();
    }
  }
}

/*******************************************************************************
*
*******************************************************************************/
void GLScene::drawGameOver() {
  // Display the game over text
  glPushMatrix();
    gameOverText->draw();
  glPopMatrix();

  // Play the game over sound
  if (!sound->getPlayedGameOver()) {
    sound->playGameOver();
    sound->setPlayedGameOver(true);
  }
}

/*******************************************************************************
*
*******************************************************************************/
void GLScene::drawHelpMenu() {
  // Display the help menu
  glPushMatrix();
    helpMenu->draw();
  glPopMatrix();
}

/*******************************************************************************
*
*******************************************************************************/
void GLScene::drawLevelComplete() {
  // Move to winning state if the last level
  if (levelLoader->getLevelNumber() == 4) {
    state = 7;
    return;
  }

  // Check the timer to transition to next level
  if (completeTimer->getTicks() > 5000) {
    // Update the game state
    state = 1;

    // Stop the timer
    completeTimer->stop();

    // Update the level loader
    switch (levelLoader->getLevelNumber()) {
      case 1:
        levelLoader->load("levels/level2");
        break;

      case 2:
        levelLoader->load("levels/level3");
        break;

      case 3:
        levelLoader->load("levels/level4");
        break;

      case 4:
        levelLoader->load("levels/level5");
        break;
    }

    // Update the player's coordinates
    player->setX(levelLoader->getStartX() + 0.2f);
    player->setY(levelLoader->getStartY());
  }

  // Display the level complete text
  glPushMatrix();
    levelCompleteText->draw();
  glPopMatrix();
}

/*******************************************************************************
*
*******************************************************************************/
void GLScene::drawPauseMenu() {
  // Display the pause menu
  glPushMatrix();
    pauseMenu->draw();
  glPopMatrix();

  // Display the dot
  glPushMatrix();
    // Set the correct translations
    dot->setModelSize(0.15f, 0.15f, 1.f);
    switch (menuState) {
      // Resume
      case 0:
        dot->setTranslateX(-5.5);
        dot->setTranslateY(2.5);
        break;

      // Menu
      case 1:
        dot->setTranslateX(-4.25);
        dot->setTranslateY(6.8);
        break;

      // Quit
      case 2:
        dot->setTranslateX(-4.25);
        dot->setTranslateY(11.0);
        break;
    }

    dot->draw();
  glPopMatrix();
}

/*******************************************************************************
*
*******************************************************************************/
void GLScene::drawStartMenu() {
  double x, y;

  // Calculate the dot's translation
  y = 12.4;
  switch (menuState) {
    // New game
    case 0:
      x = -25.0;
      break;

    // Help
    case 1:
      x = -8.5;
      break;

    // Credits
    case 2:
      x = 2.0;
      break;

    // Quit
    case 3:
      x = 16.0;
      break;
  }

  // Display the start menu
  glPushMatrix();
    startMenu->draw();
  glPopMatrix();

  // Display the particles
  glPushMatrix();
    glUseProgram(shaderLoader->getProgram());
    GLint locationR = glGetUniformLocation(shaderLoader->getProgram(), "r");
    GLint locationG = glGetUniformLocation(shaderLoader->getProgram(), "g");
    GLint locationB = glGetUniformLocation(shaderLoader->getProgram(), "b");
    if (locationR != -1 && locationG != -1 && locationB != -1) {
      glUniform1f(locationR, shaderLoader->getR());
      glUniform1f(locationG, shaderLoader->getG());
      glUniform1f(locationB, shaderLoader->getB());
      shaderLoader->updateColors();
    }

    particles->generate(x, y);
    particles->draw();
    particles->lifetime();

    glUseProgram(0);
  glPopMatrix();

  // Display the dot
  glPushMatrix();
    dot->setModelSize(0.25f, 0.25f, 1.f);
    dot->setTranslateX(x);
    dot->setTranslateY(y);
    dot->draw();
  glPopMatrix();
}

/*******************************************************************************
*
*******************************************************************************/
void GLScene::drawYouWon() {
  // Check the timer to transition back to the start menu
  if (completeTimer->getTicks() > 5000) {
    state = 0;
    sound->stopBackground();
    sound->playMenu();
  }

  // Display the you won text
  glPushMatrix();
    youWonText->draw();
  glPopMatrix();
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

  // Setup the start menu
  startMenu = new Model();
  startMenu->init("images/menu/start_menu.png");
  startMenu->setModelSize(14.f, 8.f, 1.f);
  startMenu->setTranslateX(-0.5);
  startMenu->setTranslateY(0.5);

  // Setup the help menu
  helpMenu = new Model();
  helpMenu->init("images/menu/help_menu.png");
  helpMenu->setModelSize(16.f, 9.f, 1.f);
  helpMenu->setTranslateX(-0.5);
  helpMenu->setTranslateY(0.57);

  // Setup the credits menu
  creditsMenu = new Model();
  creditsMenu->init("images/menu/credits_menu.png");
  creditsMenu->setModelSize(16.f, 9.f, 1.f);
  creditsMenu->setTranslateX(-0.5);
  creditsMenu->setTranslateY(0.57);

  // Setup the pause menu
  pauseMenu = new Model();
  pauseMenu->init("images/menu/pause_menu.png");
  pauseMenu->setModelSize(4.f, 4.2065f, 1.f);
  pauseMenu->setTranslateX(-0.5);
  pauseMenu->setTranslateY(0.5);

  // Setup the player
  player = new Player();
  player->init();
  player->setX(levelLoader->getStartX() + 0.2f);
  player->setY(levelLoader->getStartY());

  // Setup the dot
  dot = new Model();
  dot->init("images/menu/dot.png");

  // Setup the game over text
  gameOverText = new Model();
  gameOverText->init("images/menu/game_over.png");
  gameOverText->setModelSize(5.f, 0.8209f, 1.f);
  gameOverText->setTranslateX(-0.5);

  // Setup the level complete text
  levelCompleteText = new Model();
  levelCompleteText->init("images/menu/level_complete.png");
  levelCompleteText->setModelSize(5.f, 0.6889f, 1.f);
  levelCompleteText->setTranslateX(-0.5);

  // Setup the you won text
  youWonText = new Model();
  youWonText->init("images/menu/you_won.png");
  youWonText->setModelSize(5.f, 0.9726f, 1.f);
  youWonText->setTranslateX(-0.5);

  // Setup the particles
  particles = new Particles();

  // Setup the shader loader
  glewInit();
  shaderLoader = new ShaderLoader();
  shaderLoader->init("shaders/v1.vs", "shaders/f1.fs");

  // Setup the complete timer
  completeTimer = new Timer();

  // Set the other variables
  pauseFlag = false;
  state     = 0;
  menuState = 0;

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
  // No inputs should be processed if the game is in a paused state
  if (pauseFlag) {
    return 0;
  }

  // Pass the WPARAM to the inputs
  inputs->setWP(wp);

  switch (msg) {
    // Key is being held
    case WM_KEYDOWN:
      if (state == 1) {
        inputs->keyDown(player, state, sound);
      }
      else {
        inputs->keyDown(menuState, state, sound);
      }
      break;

    // Key is being released
    case WM_KEYUP:
      if (state == 1) {
        inputs->keyUp(player);
      }
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
