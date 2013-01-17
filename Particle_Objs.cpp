#include "Particle_Objs.h"

Particle_Objs::init(){
  Common cm = Common::GetInstance();
  int dataNum = cm->getDataNum();
  ps = new PointSprite();
  x = new double*[dataNum];
  x[0] = new double*[dataNum*3];
  color = new double*[dataNum];
  color[0] = new double*[dataNum*3];

}
