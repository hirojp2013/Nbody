#ifndef ANGULAR_VEL_H
#define ANGULAR_VEL_H
//#include <cave_ogl.h>
#include "GL/glut.h" 
#include "GL/gl.h"

class arrow;
class Common;

class angular_vel{
 public:

  angular_vel();
  void Cross(double *orientV,double *diff_velV,GLdouble *ang_momV);
  void draw_arrow();
  void get_inf_V(double Vec[],
		 double *angular,
		 double *azimuth,
		 double *length);
  void get_omega(double pos[][3],
		 double vel[][3],
		 double dist,
		 GLdouble omega[3]);

 private:
  arrow *aw;
  Common *cm;
};
#endif
