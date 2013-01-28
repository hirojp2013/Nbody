#include "Particle_Objs.h"

void Particle_Objs::init(){
  cm = Common::GetInstance();
  ps = new PointSprite();
  color_set();
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
  int size= 30;
  ps->drawPointSprite(x[0], color[0],id_num);
  glPopMatrix();
}

void Particle_Objs::color_set(){
  Common *cm = Common::GetInstance();
  int id_num = cm->data.getIDNum();
  for(int i=0;i<id_num;i++){
    switch( i% COLOR_NUM ){
    case 0:
      color[i][0] =1.0;
      color[i][1] =0.0;
      color[i][2] =0.0;  
      break;
    case 1:
      color[i][0] =0.0;
      color[i][1] =1.0;
      color[i][2] =0.0;  
      break;
    case 2:
      color[i][0] =0.0;
      color[i][1] =0.0;
      color[i][2] =1.0;  
      break;
    case 3:
      color[i][0] =0.0;
      color[i][1] =1.0;
      color[i][2] =1.0;  
      break;
    case 4:
      color[i][0] =1.0;
      color[i][1] =0.0;
      color[i][2] =1.0;  
      break;
    default:
      glColor3d(1.0,1.0,0.0);
      break;
    }
  }
}
