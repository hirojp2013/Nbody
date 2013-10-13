#ifndef ARROW_H
#define ARROW_H

//#include <cave_ogl.h>
#include"GL/glut.h"
#include"GL/gl.h"


class Common;

class arrow{
 public:
  arrow();

  void draw(double x,
	    double y,
	    double z,
		  double angular,
		  double azimuth,
		  double length);
  void draw(double *pos,
		  double angular,
		  double azimuth,
		  double length);

  void the_arrow();
 private:
  GLUquadricObj *clyndObj;
  GLUquadricObj *discObj;
  GLUquadricObj *sphereObj;
  GLuint theArrow;
  Common *cm;

};
#endif
