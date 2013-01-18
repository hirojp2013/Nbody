#include "Particle_Objs.h"

void Particle_Objs::init(){
  Common *cm = Common::GetInstance();
  id_num = cm->data.getIDNum();
  printf("check id_num %d\n",id_num);
  ps = new PointSprite();
  x = new double*[id_num];
  x[0] = new double[id_num*3];
  for(int i=0; i<id_num; i++){
    x[i] = x[0] + i*3;
  }

  color = new double*[id_num];
  color[0] = new double[id_num*3];
  for(int i=0; i<id_num; i++){
    color[i] = color[0] + i*3;
  }

  color_set();
}

void Particle_Objs::draw(){
  glPushMatrix();
  ps->drawPointSprite(x[0], color[0],id_num);
  glPopMatrix();
}

void Particle_Objs::color_set(){
  for(int i=0;i<id_num;i++){
    color[i][0] = 1.0;
    color[i][1] = 0.0;
    color[i][2] = 0.0;
  }
}
