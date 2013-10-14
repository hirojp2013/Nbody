/*
 * EnergyState.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef ENERGYSTATE_H_
#define ENERGYSTATE_H_

#include "VisualState.h"

class EnergyState: public VisualState {
public:
    EnergyState();
    virtual ~EnergyState();
    void visualize();
};

#endif /* ENERGYSTATE_H_ */
