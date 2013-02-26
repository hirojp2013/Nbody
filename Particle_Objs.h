#include "common.h"
#include "pointsprite.hpp"
class PointSprite;


class Particle_Objs{
 public:
  int *element_type;
  MY_VERTEX vertecies[PARTICLE_NUMBER_MAX];

  Particle_Objs();
  ~Particle_Objs();
  void  init();
  void set_vertecies(_MY_VERTEX_ myv[]);
  void draw();
 private:
  Common *cm;
  PointSprite *ps;
  void color_set();
};
