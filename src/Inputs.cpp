#include "Inputs.h"

/*******************************************************************************
*
*******************************************************************************/
Inputs::Inputs()
: mouseTranslate(false), mouseRotate(false), prevMouseX(0.0), prevMouseY(0.0) {

}

/*******************************************************************************
*
*******************************************************************************/
Inputs::~Inputs() {

}

/*******************************************************************************
*
*******************************************************************************/
void Inputs::mouseDown(Player* p, double x, double y) {
  /*// Save the coordinates
  prevMouseX = x;
  prevMouseY = y;

  switch (wp) {
    // Left button
    case MK_LBUTTON:
      mouseRotate = true;
      break;

    // Right button
    case MK_RBUTTON:
      mouseTranslate = true;
      break;

    // Middle button
    case MK_MBUTTON:
      break;
  }*/
}

/*******************************************************************************
*
*******************************************************************************/
void Inputs::mouseMove(Player* p, double x, double y) {
  /*// Translate the model
  if (mouseTranslate) {
    // Update the values
    m->setTranslateX(m->getTranslateX() + (x - prevMouseX) / 100.0);
    m->setTranslateY(m->getTranslateY() + (y - prevMouseY) / 100.0);

    // Save the coordinates
    prevMouseX = x;
    prevMouseY = y;
  }

  // Rotate the model
  if (mouseRotate) {
    // Update the values
    m->setRotateX(m->getRotateX() + (y - prevMouseY) / 3.0);
    m->setRotateY(m->getRotateY() + (x - prevMouseX) / 3.0);

    // Save the coordinates
    prevMouseX = x;
    prevMouseY = y;
  }*/
}

/*******************************************************************************
*
*******************************************************************************/
void Inputs::mouseUp() {
  /*mouseTranslate = false;
  mouseRotate    = false;*/
}

/*******************************************************************************
*
*******************************************************************************/
void Inputs::mouseWheel(Player* p, double z) {
  /*m->setZoom(m->getZoom() + z / 100.0);*/
}

/*******************************************************************************
*
*******************************************************************************/
void Inputs::keyDown(int& menuState, int& gameState, Sound* sound) {
  switch (wp) {
    // Left arrow
    case VK_LEFT:
      if (gameState != 4) {
        menuState -= 1;
        if (menuState < 0) {
          menuState = 0;
        }
      }
      break;

    // Right arrow
    case VK_RIGHT:
      if (gameState != 4) {
        menuState += 1;
        if (menuState > 3) {
          menuState = 3;
        }
      }
      break;

    // Up arrow
    case VK_UP:
      if (gameState == 4) {
        menuState -= 1;
        if (menuState < 0) {
          menuState = 0;
        }
      }
      break;

    // Down arrow
    case VK_DOWN:
      if (gameState == 4) {
        menuState += 1;
        if (menuState > 2) {
          menuState = 2;
        }
      }
      break;

    // Return key or space key
    case VK_RETURN:
    case VK_SPACE:
      if (gameState != 4) {         // Main menu
        if (menuState == 0) {
          gameState = 1;
          sound->stopMenu();
        }
        else if (menuState == 1) {
          gameState = 2;
        }
        else if (menuState == 2) {
          gameState = 3;
        }
        else if (menuState == 3) {
          gameState = -1;
        }
      }
      else {                        // Game paused
        if (menuState == 0) {
          gameState = 1;
        }
        else if (menuState == 1) {
          gameState = 0;
          menuState = 0;
          sound->stopBackground();
        }
        else if (menuState == 2) {
          gameState = -1;
        }
      }
      break;

    // Backspace key
    case VK_BACK:
      if (gameState != 4) {
        gameState = 0;
      }
      break;
  }
}

/*******************************************************************************
*
*******************************************************************************/
void Inputs::keyDown(Player* p, int& gameState) {
  switch (wp) {
    // Left arrow
    case VK_LEFT:
      p->setActionTrigger(4);
      break;

    // Right arrow
    case VK_RIGHT:
      p->setActionTrigger(3);
      break;

    // Up arrow
    case VK_UP:
      p->setActionTrigger(1);
      break;

    // Down arrow
    case VK_DOWN:
      p->setActionTrigger(2);
      break;

    // Home
    case VK_HOME:
      //m->setZoom(m->getZoom() - 1.0);
      break;

    // End
    case VK_END:
      //m->setZoom(m->getZoom() + 1.0);
      break;

    // Space
    case VK_SPACE:
      p->launchProjectile();
      break;

    // Backspace
    case VK_BACK:
      gameState = 4;
      break;
  }
}

/*******************************************************************************
*
*******************************************************************************/
void Inputs::keyUp(Player* p) {
  p->setActionTrigger(0);
}

/*******************************************************************************
*
*******************************************************************************/
void Inputs::setWP(WPARAM w) {
  wp = w;
}
