#include "Model.h"

/*******************************************************************************
*
*******************************************************************************/
Model::Model()
: rotateX(0.0), rotateY(0.0), rotateZ(0.0), translateX(0.0), translateY(0.0),
  zoom(-8.0), tileType('\0'), active(false), velocity(0.f), direction(false) {

}

/*******************************************************************************
*
*******************************************************************************/
Model::~Model() {
  delete texture;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::draw() {
  // Bind the texture
  texture->binder();

  // Scale the model
  glScalef(modelSize[0], modelSize[1], modelSize[2]);

  // Update the translations
  //double delta = 0.05;
  double delta = 0.005;
  if (active) {
    // Vertical
    if (!direction) {
      translateY += velocity * delta;
    }

    // Horizontal
    else {
      translateX += velocity * delta;
    }
  }

  // Translate the model
  glTranslated(translateX, -translateY, zoom);

  // Rotate the model
  glRotated(rotateX, 1.0, 0.0, 0.0);
  glRotated(rotateY, 0.0, 1.0, 0.0);
  glRotated(rotateZ, 0.0, 0.0, 1.0);

  // Draw the model
  glBegin(GL_QUADS);
    glTexCoord2f(0.f, 1.f);
    glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);

    glTexCoord2f(1.f, 1.f);
    glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);

    glTexCoord2f(1.f, 0.f);
    glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);

    glTexCoord2f(0.f, 0.f);
    glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
  glEnd();
}

/*******************************************************************************
*
*******************************************************************************/
double Model::getRotateX() {
  return rotateX;
}

/*******************************************************************************
*
*******************************************************************************/
double Model::getRotateY() {
  return rotateY;
}

/*******************************************************************************
*
*******************************************************************************/
char Model::getTileType() {
  return tileType;
}

/*******************************************************************************
*
*******************************************************************************/
double Model::getTranslateX() {
  return translateX;
}

/*******************************************************************************
*
*******************************************************************************/
double Model::getTranslateY() {
  return translateY;
}

/*******************************************************************************
*
*******************************************************************************/
double Model::getZoom() {
  return zoom;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::init(char* filename) {
  texture = new TextureLoader();
  texture->bindTexture(filename);
}

/*******************************************************************************
*
*******************************************************************************/
bool Model::isActive() {
  return active;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setDirection(bool d) {
  direction = d;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setActive(bool a) {
  active = a;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setModelSize(float x, float y, float z) {
  modelSize[0] = x;
  modelSize[1] = y;
  modelSize[2] = z;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setRotateX(double x) {
  rotateX = x;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setRotateY(double y) {
  rotateY = y;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setTileType(char t) {
  tileType = t;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setTranslateX(double x) {
  translateX = x;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setTranslateY(double y) {
  translateY = y;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setVelocity(float v) {
  velocity = v;
}

/*******************************************************************************
*
*******************************************************************************/
void Model::setZoom(double z) {
  zoom = z;
}
