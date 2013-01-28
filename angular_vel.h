#ifndef ANGULAR_VEL_H
#define ANGULAR_VEL_H
#include "GL/glut.h" 
#include "GL/gl.h"
#include "motion.h"
#include "arrow.h"

class angular_vel{
 public:

  angular_vel();
  void Cross(double *orientV,double *diff_velV,GLdouble *ang_momV);
  void draw_arrow();
  void get_inf_V(double Vec[],
		 double *angular,
		 double *azimuth,
		 double *length);
  void get_omega(PARTICLE_POS *pos,
		 PARTICLE_VEL *vel,
		 double dist,
		 GLdouble omega[3]);

 private:
  arrow *aw;
  Common *cm;
};
#endif
