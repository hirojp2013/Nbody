#ifndef COLOR_LEGEND_RGB
#define COLOR_LEGEND_RGB
#include "Icolor_legend.hpp"
#include<GLUT/glut.h>
#include<cmath>
#include<cstdio>
class color_legend_rgb {
public:
  color_legend_rgb(double min,double max,double dx);
  void color_map(double x,double a,GLdouble color[4]);
  void color_map(double x,GLdouble color[3]);
private:
  double max;
  double min;
  double dx;
  double dx_2;
  double cof;
  double length;
  double recp_length;
  double red_r;
  double red_l; 
  double green_r;
  double green_l;
  double blue_r;
  double blue_l;
  double red_reg2;
  double green_reg2;
  double blue_reg2;
  double solve_g(double x);
  double trape_red(double g);
  double trape_green(double g);
  double trape_blue(double g);
  GLdouble trapezoid(double g,double region2,double r,double l);
};
#endif
