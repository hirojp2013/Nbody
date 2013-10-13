#include"arrow.h"
#include "Particle.h"
#include "common.h"

arrow::arrow(){
  sphereObj = gluNewQuadric();
  clyndObj = gluNewQuadric();
  discObj = gluNewQuadric();

  theArrow = glGenLists(1);
  glNewList(theArrow,GL_COMPILE);
  the_arrow();
  glEndList();

  cm = Common::GetInstance();

}

void arrow::draw(double *pos,double angular,double azimuth,double length){
  draw((double)(pos[0]),(double)(pos[1]),(double)(pos[2]),angular,azimuth,length);
}

void arrow::draw(double x,double y,double z,double angular,double azimuth,double length){

  glPushMatrix();
  {
    glTranslated(x,y,z);
    glRotated(angular,0.0,1.0,0.0);
    glRotated(-azimuth,1.0,0.0,0.0);
    glScaled(1.0/cm->scale,1.0/cm->scale,length/cm->scale);
    glCallList(theArrow);
  }
  glPopMatrix();
}

void arrow::the_arrow(){
  gluCylinder(clyndObj,
	      ARROW_WIDTH/3.0,ARROW_WIDTH/3.0,
	      ARROW_LENGTH,16,16);
  gluDisk(discObj,0.0,ARROW_WIDTH/3.0,16,16);
  glTranslated(0.0,0.0,ARROW_LENGTH);
  gluDisk(discObj,0.0,ARROW_WIDTH,16,16);
  gluCylinder(clyndObj,ARROW_WIDTH,0.0,ARROW_LENGTH,16,16);
}

