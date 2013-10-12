/*
 * beam.cpp
 *
 *  Created on: 2013/10/12
 *      Author: hayashi
 */

#include "beam.h"
#include<GLUT/glut.h>

beam::beam() {
    sphereObj = gluNewQuadric();
    clyndObj = gluNewQuadric();
    discObj = gluNewQuadric();
    theBeam = glGenLists(1);

    glNewList(theBeam, GL_COMPILE);
    make_beam();
    glEndList();
}

beam::~beam() {
	// TODO Auto-generated destructor stub
}

void beam::make_beam(){

  glTranslated(0.0,0.0,-CROSS_LENGTH);
  gluCylinder(clyndObj,BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  gluDisk(discObj,0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);

  gluCylinder(clyndObj,BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluDisk(discObj,0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,-CROSS_LENGTH);
  glRotated(90,1.0,0.0,0.0);

  glTranslated(0.0,0.0,-CROSS_LENGTH);
  gluCylinder(clyndObj,BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  gluDisk(discObj,0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluCylinder(clyndObj,BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluDisk(discObj,0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,-CROSS_LENGTH);
  glRotated(90,1.0,0.0,0.0);

  glRotated(90,0.0,1.0,0.0);
  glTranslated(0.0,0.0,-CROSS_LENGTH);
  gluCylinder(clyndObj,BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  gluDisk(discObj,0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluCylinder(clyndObj,BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluDisk(discObj,0.0,BEAM_WIDTH,16,16);
}
