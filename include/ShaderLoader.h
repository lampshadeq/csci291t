#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class ShaderLoader {
  public:
    ShaderLoader();
    ~ShaderLoader();

    void         cleanup();
    float        getB();
    float        getG();
    unsigned int getProgram();
    float        getR();
    void         init(char*, char*);
    void         updateColors();

  private:
    void         loadFile(char*, string&);
    unsigned int loadShader(string&, unsigned int);

    float        r, g, b;
    unsigned int vs, fs, program, step;
};

#endif
