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
    ArrowState();
    virtual ~ArrowState();
    void visualize();

};

#endif /* ARROWSTATE_H_ */
