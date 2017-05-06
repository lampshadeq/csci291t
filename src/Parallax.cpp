#include "Parallax.h"

/*******************************************************************************
*
*******************************************************************************/
Parallax::Parallax()
: xMax(1.f), xMin(0.f), yMax(0.f), yMin(1.f) {

}

/*******************************************************************************
*
*******************************************************************************/
Parallax::~Parallax() {
  delete texture;
}

/*******************************************************************************
*
*******************************************************************************/
void Parallax::draw(float width, float height) {
  float aspectRatio = width / height;

  texture->binder();

  glColor3f(1.f, 1.f, 1.f);

  glBegin(GL_POLYGON);
    glTexCoord2f(xMin, yMin);
    glVertex3f(-1.f * aspectRatio, -1.f, -8.f);

    glTexCoord2f(xMax, yMin);
    glVertex3f(aspectRatio, -1.f, -8.f);

    glTexCoord2f(xMax, yMax);
    glVertex3f(aspectRatio, 1.f, -8.f);

    glTexCoord2f(xMin, yMax);
    glVertex3f(-1.f * aspectRatio, 1.f, -8.f);
  glEnd();
}

/*******************************************************************************
*
*******************************************************************************/
void Parallax::init(char* filename) {
  texture = new TextureLoader();
  texture->bindTexture(filename);
}

/*******************************************************************************
*
*******************************************************************************/
void Parallax::scroll(bool autoFlag, string direction, float speed) {
  if (autoFlag) {
    if (direction == "+x") {
      xMax += speed;
      xMin += speed;
    }
    else if (direction == "-x") {
      xMax -= speed;
      xMin -= speed;
    }
    else if (direction == "+y") {
      yMax -= speed;
      yMin -= speed;
    }
    else if (direction == "-y") {
      yMax += speed;
      yMin += speed;
    }
  }
}
