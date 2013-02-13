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
  double pos[2][3];
  double com[3];
  double vel[2][3];
  int count;
  bool tag;
  double dist;
}BINARY;

enum I_OR_O{I_TARGET =0,OTHER_TARGET = 1,};

#define BINARY_INIT {{id1,id2},{{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}},{0.0,0.0,0.0},{{0.0,0.0,0.0},{0.0,0.0,0.0}},0}
#define PARTICLE_INF_INIT {0,{0.0,0.0,0.0},{0.0,0.0,0.0},0.0,0.0,0.0,NOT_MAKE_BINARY,0.0}

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
  Common *cm;
  map<string,BINARY> bin_map;
  multimap<string,PARTICLE_INF> cell_data;
  double DIST_THRESH;
  double DIST_THRESH2;
  double COMDIFF_THRESH;
  double BIN_COUNT_THRESH;
  double BIN_REMOVE_COUNT_THRESH;
  double EPSIRON;
  double CELL_LENGTH;
  Motion();
  ~Motion() {}
  Motion(const Motion& obj);
  Motion& operator=(const Motion& obj);
  void bin_map_initialize();
  void box_initialize(int max_index);
  void FindBinary_initialize();

  void Search_icell(multimap<string,PARTICLE_INF>&cell_data,GLdouble scale,string iname,string tname);
  void Search_tcell(multimap<string,PARTICLE_INF>&cell_data,GLdouble scale,string iname,string tname);
  void Make_binary(pair<string,PARTICLE_INF> ipar,pair<string,PARTICLE_INF> tpar,GLdouble scale);

  void bin_map_erase();
  void Grid_decomp(multimap< string,PARTICLE_INF >& cell_data,double cell_length);
  double GetTotalVelocity(Particle *pt[], int num);
  void GetCOM(double pos[][3],double *com,int num);
  double GetCOMDiff(Particle *pt[], double *com_prev, int num);
};

#endif
