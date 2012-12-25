#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include<queue>
#include<cmath>

/*
 * Particle data class
 *
 *  Format: YAML
 *   x: position
 *   v: velocity
 *   a: acceleration
 *   t: time
 *  id: particle number (1 - 100)
 *

<sample>
--- !!Particle 
a: 
- -0.856500403861248
- 0.312519127614472
- -0.398282081404744
id: 1
j: 
- 0.66972929839505
- 1.23604560026317
- 0.610656076067405
t: 0.0
v: 
- 0.0947290084680426
- 0.232359468889635
- -0.370136736712907
x: 
- 0.696884292699514
- 0.0614443557808207
- 0.381760297201723

 *
 */

using namespace std;



typedef struct{
  double pos[3];
}PARTICLE_POS;


typedef struct{
    double vel[3];
}PARTICLE_VEL;

typedef struct {
    int id;
    PARTICLE_POS pos;
    PARTICLE_VEL vel;
} PARTICLE_INF;


class Particle
{
	friend class ParticleData;

protected:
	int    id;
	double x[3];
	double v[3];
	double a[3];
	double j[3];
	double t;
	double vlen;

public:
	Particle();
	~Particle() {}

	void init();
	bool isEmpty();
	void setData(string name, vector<double> &val);
	void setId(int val);
	void setTime(double val);
	void setX(const double *pos);
	int  getId() { return id; }
	double getTime() { return t; }
	double getVLen() { return vlen; }
	void getX(double *pos) { for (int i = 0; i < 3; i++) pos[i] = x[i]; }
	void getV(PARTICLE_VEL *vel,double scale=1.0) { 
	    for (int i = 0; i < 3; i++){
		vel->vel[i] = v[i]/scale; 
	    }
	}

	void getV(double *vel,double scale=1.0) { 
	    for (int i = 0; i < 3; i++){
		vel[i] = v[i]/scale; 
	    }
	}

	void getA(double *pos) { for (int i = 0; i < 3; i++) pos[i] = a[i]; }
	void getJ(double *pos) { for (int i = 0; i < 3; i++) pos[i] = j[i]; }
	void extrapolate(double tcur, double scale, PARTICLE_POS *pos);
	double max_particle_coord(PARTICLE_POS &pos);
};

class ParticleData
{

private:

	vector<Particle> data;
	int dataNum;
	double vmax;
	vector<int> curlist;
	vector<PARTICLE_INF> poslistV;
public:
	ParticleData() { dataNum = 0; vmax = 0.0; poslistV.clear();}
	~ParticleData() {}
	bool readData(const char *filename);
	int initList(void);
	double setCurrentParticle(int frame);
	double getCurrentParticleId(int frame);
	vector<int> &getCurrentList(void) { return curlist; }
	vector<PARTICLE_INF> &getCurrentPosInf(void) { return poslistV; }
	Particle *getData(int index);
	int getDataNum() { return (int)data.size(); }
	double getMaxV() { return vmax; }

};

#endif
