#ifndef ARROW_H
#define ARROW_H

#include <cave_ogl.h>
#include"GL/glut.h"
#include"GL/gl.h"


class Common;
struct pos_t;

class arrow{
 public:
  arrow();

  void draw(double x,
	    double y,
	    double z,
		  double angular,
		  double azimuth,
		  double length);
  void draw(struct pos_t pos,
		  double angular,
		  double azimuth,
		  double length);

  void the_arrow();
 private:
  GLUquadricObj *clyndObj[CAVE_MAX_WALLS];
  GLUquadricObj *discObj[CAVE_MAX_WALLS];
  GLUquadricObj *sphereObj[CAVE_MAX_WALLS];
  GLuint theArrow[CAVE_MAX_WALLS];
  Common *cm;

};
#endif
