#include "common.h"

class Particle_Obj{
 public:
  int *element_type;
  double **x;
  double **color;

  Particle_Objs(){};
  ~Particle_Objs();
  init();
 private:
  PointSprite *ps;


}
