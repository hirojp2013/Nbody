#ifndef COLOR_LEGEND_HUE
#define COLOR_LEGEND_HUE
#include "Icolor_legend.hpp"
#include"hsv.hpp"
#include<GL/glut.h>
#include<cstdio>

class color_legend_hue:public Icolor_legend{
public:
  color_legend_hue(const double min_,const double max_);
  void color_map(double x,double a,GLdouble color[4]);
  void color_map(double x,GLdouble color[3]);

private:
  double min;
  double max;
  double recp_length;
};

#endif
