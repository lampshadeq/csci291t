#ifndef PARTICLES_H
#define PARTICLES_H

#include <GL/gl.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Particles {
  public:
    Particles();
    ~Particles();

    void draw();
    void generate();
    void generate(float, float);
    void lifetime();

  private:
    struct Particle {
      bool  alive, text;
      float xpos, ypos, zpos;
      float xdir, ydir;
      float mass;
    };

    double drand();
    void   randomize(Particle&);

    float            gravity;
    int              maxParticles, numParticles;
    vector<Particle> particles;
};

#endif
