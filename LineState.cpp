/*
 * LineState.cpp
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#include "LineState.h"

LineState::LineState() {
    // TODO Auto-generated constructor stub

}

LineState::~LineState() {
    // TODO Auto-generated destructor stub
}

void LineState::visualize() {
    GLdouble omega[3];
      Motion *mo = Motion::GetInstance();
      vector< pair<string,BINARY> >binlist(mo->GetBinaryMap().begin(),
                           mo->GetBinaryMap().end());
      vector< pair<string,BINARY> >::iterator bp;
      BINARY bi_buff;
      if(cm->binary_state == LINE){
        glPushMatrix();
        glRotated(cm->theta, 0.0, 0.0, 1.0);
        glRotated(cm->phi, 1.0, 0.0, 0.0);
        glColor3d( 1.0, 1.0, 1.0 );

        glLineWidth(2.0);
        glBegin(GL_LINES);
        for(bp = binlist.begin();bp!=binlist.end();bp++){
          bi_buff = (*bp).second;
          glVertex3d(bi_buff.pos[0][0],bi_buff.pos[0][1],bi_buff.pos[0][2]);
          glVertex3d(bi_buff.pos[1][0],bi_buff.pos[1][1],bi_buff.pos[1][2]);
        }
        glEnd();
        glPopMatrix();
}
