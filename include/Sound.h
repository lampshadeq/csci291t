#ifndef SOUND_H
#define SOUND_H

#include <irrKlang/irrKlang.h>

using namespace irrklang;

class Sound {
  public:
    Sound();
    ~Sound();

    void init();
    bool isPlaying();
    void playBackground();
    void playMenu();
    void playMenuMove();
    void stopBackground();
    void stopMenu();

  private:
    bool          playing;
    ISound        *menu, *background;
    ISoundEngine* engine;
    ISoundSource* menuMove;
};

#endif
