#include "binary.h"
const double MIN = 0;
const double MAX = 1.;
binary::binary():clh(MIN,MAX){
  ang_vel = new angular_vel;
  cm = Common::GetInstance();
}

void binary::draw(){
  ang_vel->draw_arrow();
}

void binary::color_set(double kinetic,GLdouble color[3]){
  switch(cm->binary_state){
  case NEARBY:
    clh.color_map(kinetic,color);
    break;
    //  case AROUND:break;
  default:
    color[0] = 0.0;
    color[1] = 0.0;
    color[2] = 1.0;
    break;
  }
}
