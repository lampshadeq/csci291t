#include "TextureLoader.h"

/*******************************************************************************
*
*******************************************************************************/
TextureLoader::TextureLoader() {

}

/*******************************************************************************
*
*******************************************************************************/
TextureLoader::~TextureLoader() {

}

/*******************************************************************************
*
*******************************************************************************/
void TextureLoader::bindTexture(const char* filename) {
  // Setup SOIL and OpenGL for textures
  glGenTextures(1, &tex);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D, tex);
  image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);

  // Enable textures for OpenGL
  glEnable(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

/*******************************************************************************
*
*******************************************************************************/
void TextureLoader::binder() {
  glBindTexture(GL_TEXTURE_2D, tex);
}
