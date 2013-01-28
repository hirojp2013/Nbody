#include"hsv.hpp"


void hsv::hsv2rgb(float h,float s,float v,
		  double color[3]){
  int hueCase = (int)(h*6);
  float frac = 6*h-hueCase;
  float lx = v*(1-s);
  float ly = v*(1-s*frac);
  float lz = v*(1-s*(1-frac));

  switch(hueCase){
  case 0:
  case 6:
    color[0]  = v;color[1]=lz; color[2]=lx;break;
  case 1:
    color[0] = ly;color[1]=v;color[2]=lx;break;
  case 2:
    color[0]=lx;color[1]=v;color[2]=lz;break;
  case 3:
    color[0]=lx;color[1]=ly;color[2]=v;break;
  case 4:
    color[0]=lz;color[1]=lx;color[2]=v;break;
  case 5:
    color[0]=v;color[1]=lx;color[2]=ly;break;
  }
}
