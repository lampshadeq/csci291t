#ifndef PARALLAX_H
#define PARALLAX_H

#include <string>
#include <TextureLoader.h>

using namespace std;

class Parallax {
  public:
    Parallax();
    ~Parallax();

    void draw(float, float);
    void init(char*);
    void scroll(bool, string, float);

  private:
    float          xMax, xMin;
    float          yMax, yMin;
    TextureLoader* texture;
};

#endif
