/*
 * LineState.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef LINESTATE_H_
#define LINESTATE_H_

#include "common.h"
#include "VisualState.h"
#include <vector>
#include <string>
#include <utility>
class LineState: public VisualState {
public:
    LineState();
    virtual ~LineState();
    void visualize();
private:
    Common& cm;
};

#endif /* LINESTATE_H_ */
