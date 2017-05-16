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
void Particles::generate() {
  int newParticles;

  // Generate a random number of new particles to create
  newParticles = drand() * 8;

  // Ensure the total number is not more than the maximum
  if (numParticles + newParticles > maxParticles) {
    newParticles = maxParticles - numParticles;
  }

  // Create and initialize the new particles
  for (int i = numParticles; i < numParticles + newParticles; i++) {
    randomize(particles[i]);

    particles[i].alive = true;
    particles[i].text  = true;
    particles[i].zpos  = -8.0;
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
    particles[i].text  = false;
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
      if (particles[i].text) {
        if (particles[i].ypos + gravity * particles[i].mass > 1.5f) {
          particles[i].ydir *= -1.0;
        }
        else {
          particles[i].ydir -= gravity * particles[i].mass;
        }
      }

      particles[i].xpos += particles[i].xdir;
      particles[i].ypos -= particles[i].ydir;

      if (particles[i].ypos < -4.f || particles[i].xpos < -6.f ||
          particles[i].xpos > 6.f) {
        particles[i].alive = false;
      }
    }
  }
}

/*******************************************************************************
*
*******************************************************************************/
void Particles::randomize(Particle& p) {
  int r = rand() % 6;

  switch (r) {
    case 0:
      p.xpos = -2.3f;
      p.ypos = 0.6f;
      p.xdir = -0.01f;
      p.ydir = -0.005f;
      p.mass = 0.1f;
      break;

    case 1:
      p.xpos = -2.3f;
      p.ypos = 0.35f;
      p.xdir = -0.01f;
      p.ydir = -0.005f;
      p.mass = 0.5f;
      break;

    case 2:
      p.xpos = -2.3f;
      p.ypos = 0.15f;
      p.xdir = -0.01f;
      p.ydir = -0.005f;
      p.mass = 5.f;
      break;

    case 3:
      p.xpos = 2.3f;
      p.ypos = 0.15f;
      p.xdir = 0.01f;
      p.ydir = -0.005f;
      p.mass = 5.f;
      break;

    case 4:
      p.xpos = 2.3f;
      p.ypos = 0.35f;
      p.xdir = 0.01f;
      p.ydir = -0.005f;
      p.mass = 0.5f;
      break;

    case 5:
      p.xpos = 2.3f;
      p.ypos = 0.6f;
      p.xdir = 0.01f;
      p.ydir = -0.005f;
      p.mass = 0.1f;
      break;
  }
}

