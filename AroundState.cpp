/*
 * Around.cpp
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#include "AroundState.h"

AroundState::AroundState() {
    // TODO Auto-generated constructor stub

}

AroundState::~AroundState() {
    // TODO Auto-generated destructor stub
}

void ArounddState::visualize() {
    glEnable(GL_BLEND);
    for(vector<PARTICLE_INF>::iterator p_inf=poslistV.begin();p_inf!=poslistV.end();p_inf++){
      clh.color_map(p_inf->kin,around_alpha_boundary(*p_inf),color[num]);
      num++;
    }
}

