#include "Font.h"

/*******************************************************************************
*
*******************************************************************************/
Font::Font() {

}

/*******************************************************************************
*
*******************************************************************************/
Font::~Font() {

}

/*******************************************************************************
*
*******************************************************************************/
void Font::buildFont(HDC deviceContext) {
  HFONT font, oldFont;

  // Create the storage for 96 characters
  base = glGenLists(96);

  // Create the font
  font = CreateFont(-24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
                    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                    FF_DONTCARE | DEFAULT_PITCH, "Courier New");

  // Select the font
  oldFont = (HFONT) SelectObject(deviceContext, font);
  wglUseFontBitmaps(deviceContext, 32, 96, base);
  SelectObject(deviceContext, oldFont);
  DeleteObject(font);
}

/*******************************************************************************
*
*******************************************************************************/
void Font::killFont() {
  glDeleteLists(base, 96);
}

/*******************************************************************************
*
*******************************************************************************/
void Font::printText(const char* f) {
  char text[256];

  if (f == NULL) {
    return;
  }

  sprintf(text, f);

  glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
  glPopAttrib();
}
