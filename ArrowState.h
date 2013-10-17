/*
 * ArrowState.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef ARROWSTATE_H_
#define ARROWSTATE_H_

#include "VisualState.h"

class ArrowState: public VisualState {
public:

	static VisualState *GetInstance(){
		static ArrowState singleton;
		return &singleton;
	}

	void visualize();

private:
	ArrowState();
    virtual ~ArrowState();
    ArrowState& operator=(const NoVisualizeState& rhs);

};

#endif /* ARROWSTATE_H_ */
