#include "ShaderLoader.h"

/*******************************************************************************
*
*******************************************************************************/
ShaderLoader::ShaderLoader()
: vs(0), fs(0), program(0), r(0.f), g(0.f), b(0.f), step(0) {
  srand(time(NULL));
}

/*******************************************************************************
*
*******************************************************************************/
ShaderLoader::~ShaderLoader() {
  cleanup();
}

/*******************************************************************************
*
*******************************************************************************/
void ShaderLoader::cleanup() {
  glDetachShader(program, vs);
  glDetachShader(program, fs);

  glDeleteShader(vs);
  glDeleteShader(fs);

  glDeleteProgram(program);
}

/*******************************************************************************
*
*******************************************************************************/
float ShaderLoader::getB() {
  return b;
}

/*******************************************************************************
*
*******************************************************************************/
float ShaderLoader::getG() {
  return g;
}

/*******************************************************************************
*
*******************************************************************************/
unsigned int ShaderLoader::getProgram() {
  return program;
}

/*******************************************************************************
*
*******************************************************************************/
float ShaderLoader::getR() {
  return r;
}

/*******************************************************************************
*
*******************************************************************************/
void ShaderLoader::init(char* vf, char* ff) {
  string source;

  // Load the vertex shader
  loadFile(vf, source);
  vs = loadShader(source, GL_VERTEX_SHADER);

  // Load the fragment shader
  source = "";
  loadFile(ff, source);
  fs = loadShader(source, GL_FRAGMENT_SHADER);

  // Create the program to hold the shaders
  program = glCreateProgram();

  // Attach and link the shaders
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
}

/*******************************************************************************
*
*******************************************************************************/
void ShaderLoader::loadFile(char* filename, string& str) {
  ifstream ifs;
  string   temp;

  // Open the file
  ifs.open(filename);

  // Append the file's content to the string
  while (getline(ifs, temp)) {
    str += temp;
  }

  // Close the file
  ifs.close();
}

/*******************************************************************************
*
*******************************************************************************/
unsigned int ShaderLoader::loadShader(string& source, unsigned int mode) {
  char         error[1024];
  const char*  cstr;
  unsigned int id;

  // Create the shader mode
  id = glCreateShader(mode);

  // Convert source to a C-string
  cstr = source.c_str();

  // Compile the shader
  glShaderSource(id, 1, &cstr, NULL);
  glCompileShader(id);

  // Check for errors
  glGetShaderInfoLog(id, 1024, NULL, error);

  // Done
  return id;
}

/*******************************************************************************
*
*******************************************************************************/
void ShaderLoader::updateColors() {
  int threshold = 5;

  if (step == threshold - 1) {
    r = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
    g = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
    b = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
  }

  step = (step + 1) % threshold;
}


