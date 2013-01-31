#include "Particle_Objs.h"

void Particle_Objs::init(){
  ps = new PointSprite;
  if(CAVEMasterDisplay()){
    printf("%s(%d)\n",__FILE__,__LINE__);
    fflush(stdout);
  }

  printf("%s(%d)\n",__FILE__,__LINE__);
  if(CAVEMasterDisplay()){
    printf("Master %p\n",ps);
  }else{
    printf("%p\n",ps);
  }
  fflush(stdout);
  //  CAVEDisplayBarrier();
  //ps[CAVEUniqueIndex()].Load();
  //  CAVEDisplayBarrier();
  if(CAVEMasterDisplay()){
      color_set();
  }
  CAVEDisplayBarrier();
  if(CAVEMasterDisplay()){
    printf("%s(%d)\n",__FILE__,__LINE__);
    fflush(stdout);
  }
  //  CAVEDisplayBarrier();
}

void Particle_Objs::set_x(double pos[][3]){
  int id_num = cm->data.getIDNum();
  for(int i=0;i<id_num;i++){
    x[i][0] = pos[i][0];
    x[i][1] = pos[i][1];
    x[i][2] = pos[i][2];
  }
}

void Particle_Objs::set_color(double cl[][4]){
  int id_num = cm->data.getIDNum();
  for(int i=0;i<id_num;i++){
    color[i][0] = cl[i][0];
    color[i][1] = cl[i][1];
    color[i][2] = cl[i][2];
    color[i][3] = cl[i][3];
  }
}

void Particle_Objs::draw(){
  int id_num = cm->data.getIDNum();
  glPushMatrix();
  ps->drawPointSprite(x[0], color[0],id_num);
  glPopMatrix();
}

void Particle_Objs::color_set(){
    printf("%s(%d)\n",__FILE__,__LINE__);
    fflush(stdout);
  int id_num = cm->data.getIDNum();
    printf("%s(%d)\n",__FILE__,__LINE__);
    printf("%d\n",id_num);
    fflush(stdout);
  for(int i=0;i<id_num;i++){
    color[i][0] = 1.0;
    color[i][1] = 0.0;
    color[i][2] = 0.0;
  }
}
