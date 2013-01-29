#include "binary.h"
const double MIN = 0;
const double MAX = 1.;
binary::binary():clh(MIN,MAX){
  printf("%s(%d)\n",__FILE__,__LINE__);
  printf("%f,%f\n",MIN,MAX) ;
  ang_vel = new angular_vel;

}

void binary::draw(){
  ang_vel->draw_arrow();
}

void binary::color_set(double kinetic,GLdouble color[3]){
  clh.color_map(kinetic,color);
}
