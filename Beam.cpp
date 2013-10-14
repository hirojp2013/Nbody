/*
 * beam.cpp
 *
 *  Created on: 2013/10/12
 *      Author: hayashi
 */

#include "beam.h"
#include<GLUT/glut.h>

Beam::Beam() {
    sphereObj = gluNewQuadric();
    clyndObj = gluNewQuadric();
    discObj = gluNewQuadric();
    theBeam = glGenLists(1);

    glNewList(theBeam, GL_COMPILE);
    make_beam();
    glEndList();
}

Beam::~Beam() {
	// TODO Auto-generated destructor stub
}

void Beam::make_beam(){

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

/*
 void draw_beam(void)
 {

 float wandvec[3];
 float beam[3];
 CAVEGetPosition(CAVE_WAND_NAV, beam);
 CAVEGetVector(CAVE_WAND_FRONT_NAV, wandvec);
 if (!cm->beam_flag) {
 return;
 }
 glPushAttrib(GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT);
 {
 glDisable(GL_LIGHTING);
 glLineWidth(3.0);
 glPushMatrix();
 {
 glEnable(GL_LIGHTING);
 glTranslated(beam[0],beam[1],beam[2]);
 glPushMatrix();
 {
 double azimuth,angular,dist;
 double beaml=0.0;
 glColor3d(1.0,1.0,1.0);
 for(int i=0;i<3;i++){
 beaml += pow(BEAM_SCALE*wandvec[i],2.0);
 }

 cout << "main " <<
 "x " << beam[0] + (BEAM_SCALE*cm->wandvec[0])<<endl
 << "y " << beam[1] + (BEAM_SCALE*cm->wandvec[1])<<endl
 <<"z "<<beam[2] + (BEAM_SCALE*cm->wandvec[2])<<endl;

 dist = sqrt(dist);
 beaml = sqrt(beaml);
 get_angl(wandvec,&angular,&azimuth);
 glRotated(angular,0.0,1.0,0.0);
 glRotated(-azimuth,1.0,0.0,0.0);
 gluCylinder(clyndObj[CAVEUniqueIndex()],BEAM_WIDTH,BEAM_WIDTH,beaml,16,16);
 gluDisk(discObj[CAVEUniqueIndex()],0.0,BEAM_WIDTH,16,16);
 }
 glPopMatrix();
 glPushMatrix();
 {
 glTranslated(wandvec[0]*(BEAM_SCALE),wandvec[1]*(BEAM_SCALE),wandvec[2]*(BEAM_SCALE));

 glRotatef(cm->rot,0.0,1.0,0.0);
 glCallList(theBeam[CAVEUniqueIndex()]);
 }
 glPopMatrix();
 glDisable(GL_LIGHTING);
 }
 glPopMatrix();
 }
 glPopAttrib();
 }
 */
