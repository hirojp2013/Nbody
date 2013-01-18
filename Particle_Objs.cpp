#include "Particle_Objs.h"

void Particle_Objs::init(){
  Common *cm = Common::GetInstance();
  int id_num = cm->data.getIDNum();
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
  Common *cm = Common::GetInstance();
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
