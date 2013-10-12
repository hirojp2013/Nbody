/*
 * beam.h
 *
 *  Created on: 2013/10/12
 *      Author: hayashi
 */

#ifndef BEAM_H_
#define BEAM_H_

class beam {
public:
    beam();
    virtual ~beam();
    void draw beam();

private:
    GLUquadricObj *clyndObj;
    GLUquadricObj *discObj;
    GLUquadricObj *sphereObj;
    GLuint theBeam;
    void make_beam();
};

#endif /* BEAM_H_ */
