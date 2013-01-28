#ifndef ARROW_H
#define ARROW_H
#include "motion.h"

class arrow{
 public:
  arrow();

  void draw(double x,
		  double y,
		  double z,
		  double angular,
		  double azimuth,
		  double length);
  void draw(PARTICLE_POS pos,
		  double angular,
		  double azimuth,
		  double length);

  void the_arrow();
 private:
  GLUquadricObj *clyndObj[CAVE_MAX_WALLS];
  GLUquadricObj *discObj[CAVE_MAX_WALLS];
  GLUquadricObj *sphereObj[CAVE_MAX_WALLS];
  GLuint theArrow[CAVE_MAX_WALLS];
  Common *cm;

};
#endif
