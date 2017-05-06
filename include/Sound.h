#ifndef SOUND_H
#define SOUND_H

#include <irrKlang/irrKlang.h>

using namespace irrklang;

class Sound {
  public:
    Sound();
    ~Sound();

    void init();
    void playBackground();

  private:
    ISoundEngine* engine;
};

#endif
