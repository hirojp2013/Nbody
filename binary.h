#ifndef BINARY_H
#define BINARY_H

#include "color_legend_hue.hpp"

class Common;
class angular_vel;
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
  const double LENGTH; 
  double around_alpha_boundary(struct inf_t par_inf);
  double eng_sum_alpha_boundary(double length);
  double eng_sum_color_boundary(double eng_sum);
  double nearby_alpha_boundary(double length);

};
#endif
