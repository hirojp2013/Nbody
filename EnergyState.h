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

	static VisualState *GetInstance(){
		static EnergyState singleton;
		return &singleton;
	}

    void Visualize();

private:
    EnergyState();
    virtual ~EnergyState();
    EnergyState& operator=(const EnergyState& rhs);

};

#endif /* ENERGYSTATE_H_ */
