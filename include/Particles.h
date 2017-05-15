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
    void generate(float, float);
    void lifetime();

  private:
    double drand();

    struct Particle {
      bool  alive;
      float xpos, ypos, zpos;
      float xdir, ydir;
      float mass;
    };

    float            gravity;
    int              maxParticles, numParticles;
    vector<Particle> particles;
};

#endif
