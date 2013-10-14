/*
 * NearBy.cpp
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#include "NearByState.h"

NearByState::NearByState() {
    // TODO Auto-generated constructor stub

}

NearByState::~NearByState() {
    // TODO Auto-generated destructor stub
}

void NearByState::visuzlize() {
      for(vector<PARTICLE_INF>::iterator p_inf=poslistV.begin();p_inf!=poslistV.end();p_inf++){
      clh.color_map(p_inf->kin,nearby_alpha_boundary(*p_inf),color[num]);
      num++;
    }
}


