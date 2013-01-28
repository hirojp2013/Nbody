#ifndef BINARY_H
#define BINARY_H
#include "angular_vel.h"
#include "color_legend_hue.hpp"

class binary{
 public:
  binary();
  void draw();
  void color_set(double kinetic,GLdouble color[3]);
 private:
  angular_vel *ang_vel; 
  color_legend_hue clh;
  double MIN,MAX;
};
#endif
