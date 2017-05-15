#include "Sound.h"

/*******************************************************************************
*
*******************************************************************************/
Sound::Sound()
: playing(false), playedGameOver(false), background(NULL), menu(NULL) {

}

/*******************************************************************************
*
*******************************************************************************/
Sound::~Sound() {
  engine->drop();
}

/*******************************************************************************
*
*******************************************************************************/
bool Sound::backgroundOn() {
  return background != NULL;
}

/*******************************************************************************
*
*******************************************************************************/
bool Sound::getPlayedGameOver() {
  return playedGameOver;
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::init() {
  engine          = createIrrKlangDevice();
  menuMove        = engine->addSoundSourceFromFile("sounds/menu_move.wav");
  collectCheese   = engine->addSoundSourceFromFile("sounds/collect_cheese.wav");
  throwCheese     = engine->addSoundSourceFromFile("sounds/throw_cheese.wav");
  cheeseCollision = engine->addSoundSourceFromFile("sounds/co_collision.wav");
  gameOver        = engine->addSoundSourceFromFile("sounds/game_over.wav");
  victory         = engine->addSoundSourceFromFile("sounds/victory.wav");

  menuMove->setDefaultVolume(0.25f);
  collectCheese->setDefaultVolume(0.5f);
  throwCheese->setDefaultVolume(0.5f);
  cheeseCollision->setDefaultVolume(0.5f);
  gameOver->setDefaultVolume(0.5f);
  victory->setDefaultVolume(0.5f);
}

/*******************************************************************************
*
*******************************************************************************/
bool Sound::isPlaying() {
  return playing;
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::playBackground() {
  background = engine->play2D("sounds/techno_chicken.wav", true, false, true);
  playing    = true;

  background->setVolume(0.4f);
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::playCheeseCollision() {
  engine->play2D(cheeseCollision);
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::playCollectCheese() {
  engine->play2D(collectCheese);
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::playGameOver() {
  engine->play2D(gameOver);
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::playMenu() {
  menu    = engine->play2D("sounds/menu.wav", true, false, true);
  playing = true;
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::playMenuMove() {
  engine->play2D(menuMove);
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::playThrowCheese() {
  engine->play2D(throwCheese);
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::playVictory() {
  engine->play2D(victory);
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::setPlayedGameOver(bool g) {
  playedGameOver = g;
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::stopBackground() {
  background->stop();
  background->drop();

  background = NULL;
  playing    = false;
}

/*******************************************************************************
*
*******************************************************************************/
void Sound::stopMenu() {
  menu->stop();
  menu->drop();

  menu    = NULL;
  playing = false;
}

