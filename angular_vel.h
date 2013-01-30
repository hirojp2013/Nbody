#ifndef ANGULAR_VEL_H
#define ANGULAR_VEL_H
#include <cave_ogl.h>
#include "GL/glut.h" 
#include "GL/gl.h"

class arrow;
class Common;
struct pos_t;
struct vel_t;

class angular_vel{
 public:

  angular_vel();
  void Cross(double *orientV,double *diff_velV,GLdouble *ang_momV);
  void draw_arrow();
  void get_inf_V(double Vec[],
		 double *angular,
		 double *azimuth,
		 double *length);
  void get_omega(pos_t *pos,
		 vel_t *vel,
		 double dist,
		 GLdouble omega[3]);

 private:
  arrow *aw;
  Common *cm;
};
#endif
