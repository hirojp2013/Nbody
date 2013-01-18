#include "common.h"
#include "pointsprite.h"

class Particle_Objs{
 public:
  int *element_type;
  double **x;
  double **color;
  int id_num;

  Particle_Objs(){};
  ~Particle_Objs();
  void  init();
  void draw();

 private:
  PointSprite *ps;

  void color_set();

};
