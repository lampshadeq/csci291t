#include "GLLight.h"

/*******************************************************************************
*
*******************************************************************************/
GLLight::GLLight() {
  // Enable lighting in OpenGL
  glEnable(GL_LIGHTING);
}

/*******************************************************************************
*
*******************************************************************************/
GLLight::~GLLight() {

}

/*******************************************************************************
*
*******************************************************************************/
GLvoid GLLight::setupLight(GLenum light) {
  // Enable the light in OpenGL
  glEnable(light);

  // Set the light characteristics
  glLightfv(light, GL_AMBIENT, lightAmbient);
  glLightfv(light, GL_DIFFUSE, lightDiffuse);
  glLightfv(light, GL_SPECULAR, lightSpecular);
  glLightfv(light, GL_POSITION, lightPosition);

  // Set the material characteristics
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
  glMaterialfv(GL_FRONT, GL_SHININESS, highShininess);
}
