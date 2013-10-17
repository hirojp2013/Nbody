/*
 * NoVisualizeState.h
 *
 *  Created on: 2013/10/14
 *      Author: hayashi
 */

#ifndef NOVISUALIZESTATE_H_
#define NOVISUALIZESTATE_H_

#include "VisualState.h"

using namespace std;

class NoVisualizeState: public VisualState {
public:

    static VisualState *GetInstance() {
        static NoVisualizeState singleton;
        return &singleton;
    }

    void Visualize();
    void SetColor();
private:
    NoVisualizeState();
    virtual ~NoVisualizeState();
    NoVisualizeState& operator=(const NoVisualizeState& rhs);
};

#endif /* NOVISUALIZESTATE_H_ */
