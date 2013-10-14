/*
 * Around.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef AROUND_H_
#define AROUND_H_

#include "VisualState.h"

class AroundState: public VisualState {
public:
    AroundState();
    virtual ~AroundState();
    void visualize();
};

#endif /* AROUND_H_ */
