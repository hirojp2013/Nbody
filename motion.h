#ifndef _MOTION_H_
#define _MOTION_H_
#include<ctime>
#include<algorithm>
#include "common.h"


typedef struct{
  int id[2];
  PARTICLE_POS pos[2];
  PARTICLE_POS com;
  PARTICLE_VEL vel[2];
  int count;
  bool tag;
}BINARY2;


typedef struct{
  int x;
  int y;
  int z;
}POS_KEY;

enum I_OR_O{I_TARGET =0,OTHER_TARGET = 1,};

#define BINARY_INIT {{id1,id2},{{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}},{0.0,0.0,0.0},{{0.0,0.0,0.0},{0.0,0.0,0.0}},0}

typedef vector< vector<PARTICLE_INF> >LINE_;
typedef vector< LINE_ >SQUARE_;
typedef vector< SQUARE_> BOX_;

class Motion {

 public:
  static Motion *GetInstance() {
    static Motion motion;
    return &motion;
  }
  void init();

  void Find_io_CellBinary(vector<PARTICLE_INF>& ilist,vector<PARTICLE_INF>& target_list,
			  double scale,I_OR_O I_O);
  void bin_map_to_binary_list();
  void FindBinary(double tcur,double scale,double length);
  void FindBinary(double tcur,double scale);
  vector<BINARY2>& GetBinary_List(){return binary_list;}

 private:
  map<string,BINARY2> bin_map;
  vector<BINARY2> binary_list;
  vector<POS_KEY> key_list;
  BOX_ cell_data;
  double DIST_THRESH;
  double COMDIFF_THRESH;
  double BIN_COUNT_THRESH;
  double BIN_REMOVE_COUNT_THRESH;
  double EPSIRON;
  double CELL_LENGTH;
  Motion() { DIST_THRESH = .1; COMDIFF_THRESH = 0; BIN_COUNT_THRESH = 0; BIN_REMOVE_COUNT_THRESH = 0;EPSIRON = DIST_THRESH/4.0; CELL_LENGTH = DIST_THRESH;

  }
  ~Motion() {}
  Motion(const Motion& obj);
  Motion& operator=(const Motion& obj);
  void bin_map_initialize();
  void box_initialize(int max_index);
  void FindBinary_initialize();
  bool isInBox(int x,int y,int z,int max_index);
  void bin_map_erase();
  void Grid_decomp(double half_length,double cell_length);
  double GetTotalVelocity(Particle *pt[], int num);
  void GetCOM(PARTICLE_POS *pos,PARTICLE_POS *com,int num);
  double GetCOMDiff(Particle *pt[], double *com_prev, int num);
};

#endif
