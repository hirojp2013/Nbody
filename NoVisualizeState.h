/*
 * NoVisualizeState.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef NOVISUALIZESTATE_H_
#define NOVISUALIZESTATE_H_

#include "VisualState.h"

class NoVisualizeState: public VisualState {
public:
    NoVisualizeState();
    virtual ~NoVisualizeState();
    void visualize();
};

#endif /* NOVISUALIZESTATE_H_ */
