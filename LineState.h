/*
 * LineState.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef LINESTATE_H_
#define LINESTATE_H_

#include "VisualState.h"

class LineState: public VisualState {
public:
    LineState();
    virtual ~LineState();
    void visualize();
};

#endif /* LINESTATE_H_ */
