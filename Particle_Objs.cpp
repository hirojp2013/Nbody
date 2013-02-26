#include "Particle_Objs.h"
#include "pointsprite.hpp"

Particle_Objs::Particle_Objs(){
  //    printf("%s(%d)\n",__FILE__,__LINE__);
  cm = Common::GetInstance();
  //    printf("%s(%d)\n",__FILE__,__LINE__);
}

void Particle_Objs::init(){
  ps = new PointSprite;
  CAVEDisplayBarrier();
}

void Particle_Objs::draw(){
  int id_num = cm->data.getIDNum();
  glPushMatrix();
  /*  vertecies[0].vPos[0] = 0.0;
  vertecies[0].vPos[1] = 0.0;
  vertecies[0].vPos[2] = 0.0;
  vertecies[0].vColor[0] = 1.0;
  vertecies[0].vColor[1] = 0.0;
  vertecies[0].vColor[2] = 0.0;
  vertecies[0].vColor[3] = 1.0;*/
  ps->drawPointSprite( vertecies,100);
  glPopMatrix();
}

void Particle_Objs::set_vertecies(MY_VERTEX myv[]){
  int id_num = cm->data.getIDNum();
  for(int i= 0;i<id_num;i++){
    vertecies[i] = myv[i];
  }
}

void Particle_Objs::color_set(){
  int id_num = cm->data.getIDNum();
  for(int i=0;i<id_num;i++){
    vertecies[i].vColor[0] = 1.0;
    vertecies[i].vColor[1] = 0.0;
    vertecies[i].vColor[2] = 0.0;
  }
}
