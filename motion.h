#ifndef _MOTION_H_
#define _MOTION_H_
#include<ctime>
#include<algorithm>

#include"Particle.h"

class Common;

typedef struct{
  int x;
  int y;
  int z;
}POS_KEY;

typedef struct{
  int id[2];
  PARTICLE_POS pos[2];
  PARTICLE_POS com;
  PARTICLE_VEL vel[2];
  int count;
  bool tag;
  double dist;
}BINARY;

enum I_OR_O{I_TARGET =0,OTHER_TARGET = 1,};

#define BINARY_INIT {{id1,id2},{{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}},{0.0,0.0,0.0},{{0.0,0.0,0.0},{0.0,0.0,0.0}},0}
#define PARTICLE_INF_INIT {0,{0.0,0.0,0.0},{0.0,0.0,0.0},0.0,0.0,NOT_MAKE_BINARY,0.0}

class Motion{ 

 public:
  static Motion *GetInstance() {
    static Motion motion;
    return &motion;
  }

  void init();

  void FindBinary(GLdouble tcur,GLdouble scale);
  map<string, BINARY>& GetBinaryMap() { return bin_map; }
  multimap<string,PARTICLE_INF>& GetCellMap(){return cell_data;}
 private:
  map<string,BINARY> bin_map;
  multimap<string,PARTICLE_INF> cell_data;
  double DIST_THRESH;
  double DIST_THRESH2;
  double COMDIFF_THRESH;
  double BIN_COUNT_THRESH;
  double BIN_REMOVE_COUNT_THRESH;
  double EPSIRON;
  double CELL_LENGTH;
  Motion()
    { DIST_THRESH = .1; COMDIFF_THRESH = 0; BIN_COUNT_THRESH = 0; BIN_REMOVE_COUNT_THRESH = 0;EPSIRON = DIST_THRESH/4.0; CELL_LENGTH = DIST_THRESH;
    DIST_THRESH2 = DIST_THRESH*DIST_THRESH;
  }
  ~Motion() {}
  Motion(const Motion& obj);
  Motion& operator=(const Motion& obj);
  void bin_map_initialize();
  void box_initialize(int max_index);
  void FindBinary_initialize();
  void Find_io_CellBinary(multimap<string,PARTICLE_INF>&cell_data, GLdouble scale,I_OR_O I_O,string iname,string tname,vector<PARTICLE_INF>& poslistV);
  void bin_map_erase();
  void Grid_decomp(multimap< string,PARTICLE_INF >& cell_data,double cell_length);
  double GetTotalVelocity(Particle *pt[], int num);
  void GetCOM(PARTICLE_POS *pos,PARTICLE_POS *com,int num);
  double GetCOMDiff(Particle *pt[], double *com_prev, int num);
};

#endif
