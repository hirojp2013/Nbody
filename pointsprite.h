#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>


class PointSprite{
 public:
  PointSprite();
  ~PointSprite();
  void drawPointSprite(GLdouble* vertices, GLdouble* color, GLsizei count);
  void drawPointSprite(GLdouble* vertices, GLdouble* color, GLsizei count, GLdouble* size);
  
 private:
  GLuint texture_name;
  static const GLfloat distance[];
  
  void loadTexture();
  
};
