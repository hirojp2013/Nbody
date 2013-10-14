/*
 * EnergyState.cpp
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#include "EnergyState.h"

EnergyState::EnergyState() {
    // TODO Auto-generated constructor stub

}

EnergyState::~EnergyState() {
    // TODO Auto-generated destructor stub
}

void EnergyState::visualize() {
    glEnable(GL_BLEND);
    for(vector<PARTICLE_INF>::iterator p_inf=poslistV.begin();p_inf!=poslistV.end();p_inf++){
      clh.color_map(eng_sum_color_boundary(*p_inf),
            eng_sum_alpha_boundary(*p_inf),
            color[num]);
      num++;
    }
}

