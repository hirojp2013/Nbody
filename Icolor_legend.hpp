#ifndef ICOLOR_LEGEND
#define ICOLOR_LEGEND
#include<GLUT/glut.h>
class Icolor_legend{
public:
  virtual void color_map(double x, double a,GLdouble color[4]) = 0;
  virtual void color_map(double x,GLdouble color[3]) = 0;
};

#endif
