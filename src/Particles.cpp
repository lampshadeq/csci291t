#include "Particles.h"

/*******************************************************************************
*
*******************************************************************************/
Particles::Particles()
: maxParticles(10000), numParticles(0), gravity(-0.0003f) {
  srand(time(NULL));
  particles.resize(maxParticles);
}

/*******************************************************************************
*
*******************************************************************************/
Particles::~Particles() {

}

/*******************************************************************************
*
*******************************************************************************/
double Particles::drand() {
  return (rand() % 1000) / 1000.0;
}

/*******************************************************************************
*
*******************************************************************************/
void Particles::draw() {
  glPointSize(5.f);

  glBegin(GL_POINTS);
    for (int i = 0; i < numParticles; i++) {
      if (particles[i].alive) {
        glVertex3f(particles[i].xpos, particles[i].ypos, particles[i].zpos);
      }
    }
  glEnd();
}

/*******************************************************************************
*
*******************************************************************************/
void Particles::generate(float dx, float dy) {
  int newParticles;

  // Factor the dot's x and y
  dx /= 4.7f;
  dy /= -4.6f;

  // Generate a random number of new particles to create
  newParticles = drand() * 3;

  // Ensure the total number is not more than the maximum
  if (numParticles + newParticles > maxParticles) {
    newParticles = maxParticles - numParticles;
  }

  // Create and initialize the new particles
  for (int i = numParticles; i < numParticles + newParticles; i++) {
    particles[i].alive = true;
    particles[i].xpos  = dx + 0.3 * drand();
    particles[i].ypos  = dy + 0.1 * drand();
    particles[i].zpos  = -8.0;
    particles[i].xdir  = 0.0;
    particles[i].ydir  = 0.0075 + 0.025 * drand();
    particles[i].mass  = 1.5 + 0.5 * drand();
  }

  // Update the number of particles
  numParticles += newParticles;
  if (numParticles >= maxParticles) {
    numParticles = 0;
  }
}

/*******************************************************************************
*
*******************************************************************************/
void Particles::lifetime() {
  // Update each particle
  for (int i = 0; i < numParticles; i++) {
    if (particles[i].alive) {
      /*if (particles[i].ypos + gravity * particles[i].mass < 0.0) {
        particles[i].ydir *= -1.0;
      }
      else {
        particles[i].ydir += gravity * particles[i].mass;
      }*/

      //particles[i].xpos += particles[i].xdir;
      particles[i].ypos -= particles[i].ydir;

      if (particles[i].ypos < -4.0) {
        particles[i].alive = false;
      }
    }
  }
}

