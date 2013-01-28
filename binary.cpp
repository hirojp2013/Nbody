#include"binary.h"
binary::binary(){
  ang_vel = new angular_vel;
}

void binary::draw(){
  ang_vel->draw_arrow();
}
