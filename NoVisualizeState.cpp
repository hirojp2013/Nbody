/*
 * NoVisualizeState.cpp
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#include "NoVisualizeState.h"

NoVisualizeState::NoVisualizeState() {
    // TODO Auto-generated constructor stub

}

NoVisualizeState::~NoVisualizeState() {
    // TODO Auto-generated destructor stub
}

void NoVisualizeState::Visualize() {
    for(int i=0;i<PARTICLE_NUMBER_MAX;i++){
        color[i][0] = 0.0;
        color[i][1] = 0.0;
        color[i][2] = 1.0;
        color[i][3] = 1.0;
      }

      break;
}
