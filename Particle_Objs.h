#include "common.h"
#include "pointsprite.h"

class Particle_Objs{
 public:
  int *element_type;
  double **x;
  double **color;

  Particle_Objs(){};
  ~Particle_Objs();
  void  init();
  void set_x(double pos[][3]);
  void set_color(double cl[][4]);
  void draw();

 private:
  PointSprite *ps;

  void color_set();

};
