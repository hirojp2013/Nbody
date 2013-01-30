#ifndef BINARY_H
#define BINARY_H

#include "color_legend_hue.hpp"

class Common;
class angular_vel;
//struct PARTICLE_INF;
struct inf_t;

class binary{
 public:
  binary(const double length);
  void draw();
  void color_set(struct inf_t p_inf,GLdouble color[4]);
 private:
  Common *cm;
  angular_vel *ang_vel; 
  color_legend_hue clh;
  const static double MIN =0.,MAX = 1.;
  const double RECIP_LENGTH; 
  double pot_alph_value_bounday(double length);
};
#endif
