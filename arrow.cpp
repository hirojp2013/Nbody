#include"arrow.h"
arrow::arrow(){
  sphereObj[CAVEUniqueIndex()] = gluNewQuadric();
  clyndObj[CAVEUniqueIndex()] = gluNewQuadric();
  discObj[CAVEUniqueIndex()] = gluNewQuadric();

  theArrow[CAVEUniqueIndex()] = glGenLists(1);
  glNewList(theArrow[CAVEUniqueIndex()],GL_COMPILE);
  the_arrow();
  glEndList();

  cm = Common::GetInstance();

}

void arrow::draw(PARTICLE_POS pos,double angular,double azimuth,double length){
  draw((double)(pos.pos[0]),(double)(pos.pos[1]),(double)(pos.pos[2]),angular,azimuth,length);
}

void arrow::draw(double x,double y,double z,double angular,double azimuth,double length){

  glPushMatrix();
  {
    glTranslated(x,y,z);
    glRotated(angular,0.0,1.0,0.0);
    glRotated(-azimuth,1.0,0.0,0.0);
    glScaled(1.0/cm->scale,1.0/cm->scale,length/cm->scale);
    glCallList(theArrow[CAVEUniqueIndex()]);
  }
  glPopMatrix();
}

void arrow::the_arrow(){
  gluCylinder(clyndObj[CAVEUniqueIndex()],
	      ARROW_WIDTH/3.0,ARROW_WIDTH/3.0,
	      ARROW_LENGTH,16,16);
  gluDisk(discObj[CAVEUniqueIndex()],0.0,ARROW_WIDTH/3.0,16,16);
  glTranslated(0.0,0.0,ARROW_LENGTH);
  gluDisk(discObj[CAVEUniqueIndex()],0.0,ARROW_WIDTH,16,16);
  gluCylinder(clyndObj[CAVEUniqueIndex()],ARROW_WIDTH,0.0,ARROW_LENGTH,16,16);
}

