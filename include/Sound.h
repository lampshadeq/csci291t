#ifndef SOUND_H
#define SOUND_H

#include <irrKlang/irrKlang.h>

using namespace irrklang;

class Sound {
  public:
    Sound();
    ~Sound();

    bool backgroundOn();
    bool getPlayedGameOver();
    void init();
    bool isPlaying();
    void playBackground();
    void playCheeseCollision();
    void playCollectCheese();
    void playGameOver();
    void playMenu();
    void playMenuMove();
    void playThrowCheese();
    void playVictory();
    void setPlayedGameOver(bool);
    void stopBackground();
    void stopMenu();

  private:
    bool          playing, playedGameOver;
    ISound        *menu, *background;
    ISoundEngine* engine;
    ISoundSource  *menuMove, *collectCheese, *throwCheese, *cheeseCollision,
                  *gameOver, *victory;
};

#endif
