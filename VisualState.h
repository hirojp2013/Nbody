/*
 * VisualState.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef VISUALSTATE_H_
#define VISUALSTATE_H_

class VisualState {
public:
    VisualState();
    virtual ~VisualState();
    virtual void visualize() = 0;
};

#endif /* VISUALSTATE_H_ */
