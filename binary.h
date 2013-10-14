#ifndef BINARY_H
#define BINARY_H

#include "color_legend_hue.hpp"
#include "VisualState.h"
class Common;
class angular_vel;
struct inf_t;

class binary{
 public:
  binary(const double length);
  void draw_arrow();
  void draw_line();
  //  void color_set(struct inf_t p_inf,GLdouble color[4]);
  void color_set(GLdouble color[][4]);
 private:
  Common *cm;
  angular_vel *ang_vel; 
  color_legend_hue clh;
  VisualState& state;
  const static double MIN =0.,MAX = 1.;
  const double LENGTH; 
  double around_alpha_boundary(struct inf_t par_inf);
  double eng_sum_alpha_boundary(struct inf_t par_inf);
  double eng_sum_color_boundary(struct inf_t par_inf);
  double nearby_alpha_boundary(struct inf_t par_inf);

  void setState(const VisualState& state);
  void requestVisualize();
};
#endif
