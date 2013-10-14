/*
 * ArrowState.cpp
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#include "ArrowState.h"

ArrowState::ArrowState() {
    // TODO Auto-generated constructor stub

}

ArrowState::~ArrowState() {
    // TODO Auto-generated destructor stub
}

void ArrowState::visualize() {
    if(cm->binary_state == ARROW){
      printf("state ARROW\n");
      ang_vel->draw_arrow();
    }
}
