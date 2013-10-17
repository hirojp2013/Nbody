/*
 * NearBy.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef NEARBY_H_
#define NEARBY_H_

#include "VisualState.h"

class NearByState: public VisualState {
public:

	static VisualState *GetInstance(){
		static EnergyState singleton;
		return &singleton;
	}

	void Visualize();
private:
    NearByState();
    virtual ~NearByState();
    void visualization();
};

#endif /* NEARBY_H_ */