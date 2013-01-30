#ifndef BINARY_H
#define BINARY_H
#include "angular_vel.h"
#include "color_legend_hue.hpp"
#include "common.h"
class binary{
 public:
  binary(const double length);
  void draw();
  void color_set(PARTICLE_INF p_inf,GLdouble color[4]);
 private:
  Common *cm;
  angular_vel *ang_vel; 
  color_legend_hue clh;
  const static double MIN =0.,MAX = 1.;
  const double RECIP_LENGTH; 
  double pot_alph_value_bounday(double length);
};
#endif
