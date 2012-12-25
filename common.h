#ifndef _COMMON_H_
#define _COMMON_H_

#include "Particle.h"

const double COLORS[][3] = {
  { 1.0, 0.0, 0.0 }, 
  { 0.0, 1.0, 0.0 }, 
  { 0.0, 0.0, 1.0 }, 
  { 0.0, 1.0, 1.0 }, 
  { 1.0, 0.0, 1.0 }, 
  { 1.0, 1.0, 0.0 }
};
const int      COLOR_NUM = sizeof(COLORS) / sizeof(COLORS[0]);
const double SIZE = 0.004;  // particle size
const double SCALE_UNIT = 1.0005;

const double   GRID_MAX = 50.0;
const double   GRID_MIN = -GRID_MAX;
const double   GRID_INTERVAL = 1.0;
const int      GRID_NUM = (int)(GRID_MAX / GRID_INTERVAL) + 1;
const float    V_NAV = 2.0f;

const double ORIG[] = { 0.0, 5.0, -2.0 };

typedef struct {
  double x;
  double y;
  double z;
  float color[3];
} TARGET_POS;

const double BEAM_SCALE = 1.7;
const double CROSS_LENGTH = 0.1; 
const double BEAM_WIDTH = 0.02;
const double HIT_SCALE = 1.2;
const double TARGET_DIST_THRESH = 0.10;
const double ARROW_LENGTH=0.010;
const double ARROW_WIDTH=0.025;
const int    TRAJ_MAX = 300;     //kiseki no youryou
const double TRAJ_COLOR_BASE = 0.2;  // kiseki no noutan no kizyun
const float SPEED = .009;
const float ROT_SPEED = 0.1;

class Common {

 public:
  static Common *GetInstance()
    {
      static Common common;
      return &common;
    }

  ParticleData data;
  vector<double> test_test;
  int      display_num;
	
  double   t_sys;                 // time
  double   interval;
  int      frame;                 // frame number
  int      frame_max;
	
  double   t_dat;                 // time (particle data)
  double   t_dat_max; 
  int      frame_dat;
  int      frame_dat_prev;
	
  int      runstate;              // status (0:stop  1:run)
  int      inc;     
  int char_state;
  // frame increment per step
  bool     is_acc;                // accelerate
  bool     is_dec;                // decelerate
  double scale;                 // scale of the system
  double radius;                // particle radius
  double theta;                 // angle of rotation around z-axis
  double phi;                   // angle of rotation around x-axis
  double dx;                    // target position x (gluLookAt)
  double dy;                    // target position y (gluLookAt)
  double dd;                    // unit of movement of the target position

  queue< vector<TARGET_POS> > traj ;
  bool         beam_flag;
  bool         beam_clear_flag;
  float rot;
  double       vmax;

  //int target_id;
  queue<int>  target_id;
  double GetRadius() { return SIZE / scale * radius; }
  double GetParticleDist(PARTICLE_POS *p1,PARTICLE_POS *p2);

  void clearTraj();
  void clearId();
  void allClear();

  void SelectParticle();
  void coordtrans(float *orig_pos,float *dis_pos,float rot);

 private:

  Common();
  ~Common();
  Common(const Common& obj);
  Common operator=(const Common& obj);

};

#endif
