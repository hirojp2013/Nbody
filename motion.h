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
  double dist;
}BINARY;



#define BINARY_INIT {{id1,id2},{{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}},{0.0,0.0,0.0},{{0.0,0.0,0.0},{0.0,0.0,0.0}},0}

class Motion {

 public:
  static Motion *GetInstance() {
    static Motion motion;
    return &motion;
  }

  void init();

  void FindBinary(GLdouble tcur,GLdouble scale);
  *BINARY GetBinaryList() { return binlist; }

 private:

  double DIST_THRESH;
  double DIST_THRESH2;
  double COMDIFF_THRESH;
  double BIN_COUNT_THRESH;
  double BIN_REMOVE_COUNT_THRESH;
  double EPSIRON;
  double CELL_LENGTH;
  int MAX_INDEX;
  int MAX_PARTICLE_NUM;
  int BINARY_MAX;
  int MAX_PARTICLE_NUMBER_PER_ONE_PARTICLE;
  typedef struct{

    int x,y,z;
  }POS_KEY;

  typedef struct{
    int par_num_per_cell;
    PARTICLE_INF par_inf_list[MAX_PARTICLE_NUM];
  }CELL;


  /*
 ***Is it anything wrong if structure HISTORY is composed of dataNum 
 ***over dataNum?
 ***You can easily access the memory you want with id_num
 *** like history[31][20].  
 */
  typedef struct{
    n_coutpt;
    coutpt_id_list[MAX_PARTICLE_NUMBER_PER_ONE_PARTICLE];
    hist_list[MAX_PARTICLE_NUMBER_PER_ONE_PARTICLE];
  }HISTORY;

  CELL cell_data[MAX_INDEX][MAX_INDEX][MAX_INDEX];
  int bi_num;
  POS_KEY pos_key_list[BINARY_MAX];
  HISTORY *history;
  BINARY binlist[BINARY_MAX];
  Motion()
    { DIST_THRESH = .1; COMDIFF_THRESH = 0; BIN_COUNT_THRESH = 0; BIN_REMOVE_COUNT_THRESH = 0;EPSIRON = DIST_THRESH/4.0; CELL_LENGTH = DIST_THRESH;
    DIST_THRESH2 = DIST_THRESH*DIST_THRESH;
    MAX_INDEX = 200;
    MAX_PARTICLE_NUM = 100;
    BINARY_MAX = 1000;
    MAX_PARTICLE_NUMBER_PER_ONE_PARTICLE = 100;
    Common *cm = Common::GetInstance();
    history = new HITORY[cm->dataNum];
  }
  ~Motion() {}
  Motion(const Motion& obj);
  Motion& operator=(const Motion& obj);
  void FindBinary_initialize();
  void Find_I_CellBinary(GLdouble scale,POS_KEY ikey);
  void delete_cell(POS_KEY pos_key);
  void Grid_decomp(double cell_length);
  int get_hist_len(int min_id,int max_id);
  double GetTotalVelocity(Particle *pt[], int num);
  void GetCOM(PARTICLE_POS *pos,PARTICLE_POS *com,int num);
  double GetCOMDiff(Particle *pt[], double *com_prev, int num);
};

#endif
