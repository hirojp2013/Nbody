#include "binary.h"
double MIN = 0;
double MAX = 1.;
binary::binary():MIN(0.0),MAX(1.0),clh(0.0,1.0){
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
