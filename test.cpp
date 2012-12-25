#include<vector>
#include<map>
#include<iostream>
#include"common.h"
#include"motion.h"
#include"motion_original.h"
#include"Particle.h"
using namespace std;
static Common *cm = NULL;
void init(const char* filename)
{
  bool ret = cm->data.readData(filename);
  if (!ret) {
    cout << "Can't read the input data." << endl;
    exit(-1);
  }
  cm->t_dat_max = cm->data.getData(cm->data.getDataNum() - 1)->getTime();
  cm->frame_max = (int)(cm->t_dat_max / cm->interval) + 1;
  cm->frame_dat = cm->data.initList() - 1;
  cout << setprecision(15)
       << "time_max: " << cm->t_dat_max
       << " interval: " << cm->interval
       << " frame_max: " << cm->frame_max
       << " vmax: " << cm->vmax
       << endl;
  cout << setprecision(15)
       << "frame_dat: " << cm->frame_dat << " t_dat: " << cm->t_dat << endl;
  
#if 0
  printf("INPUT --------------------------------------------\n");
  for (int i = 0; i < cm->data.getDataNum(); i++) {
    double va[3], vj[3], vv[3], vx[3];
    Particle *p = cm->data.getData(i);
    printf("--- !!Particle \n");
    p->getA(va);
    printf("a: \n");
    for (int j = 0; j < 3; j++) {
      printf("- %.15g\n", va[j]);
    }
    printf("id: %d\n", p->getId());
    p->getJ(vj);
    printf("j: \n");
    for (int j = 0; j < 3; j++) {
      printf("- %.15g\n", vj[j]);
    }
    printf("t: %.15g\n", p->getTime());
    p->getV(vv);
    printf("v: \n");
    for (int j = 0; j < 3; j++) {
      printf("- %.15g\n", vv[j]);
    }
    p->getX(vx);
    printf("x: \n");
    for (int j = 0; j < 3; j++) {
      printf("- %.15g\n", vx[j]);
    }
  }
  printf("INPUT end ----------------------------------------\n");
#endif
}

void step(void)
{
  vector<int> curlist = cm->data.getCurrentList();
  vector<int>::iterator p;
  PARTICLE_POS pos;
  PARTICLE_INF pos_inf;
  double incl = 0.001;
  vector<PARTICLE_INF>&poslistV = cm->data.getCurrentPosInf();
  poslistV.clear();
  if (cm->runstate == 0) {
    Motion::GetInstance()->init();
    Motion_original::GetInstance()->init();
    if (cm->is_acc && cm->interval + incl < 1.0) {
      cm->interval += incl;
      cm->is_acc = false;
    }
    if (cm->is_dec && cm->interval - incl > 0.001) {
      cm->interval -= incl;
      cm->is_dec = false;
    }
    double max_length = -1.;
    for (p = curlist.begin(); p != curlist.end(); p++) {
      if(*p<0){
	continue;
      }
      Particle *pt = cm->data.getData(*p);
      double length_cand;
      pt->extrapolate(cm->t_dat, cm->scale, &pos);
      pos_inf.id = pt->getId();
      pos_inf.pos = pos;
      length_cand = pt->max_particle_coord(pos);
      max_length = max(max_length,length_cand);
      pt->getV(&(pos_inf.vel),cm->scale);
      poslistV.push_back(pos_inf);
    }
    Motion::GetInstance()->FindBinary(cm->t_dat,cm->scale,max_length);
    Motion_original::GetInstance()->FindBinary(cm->t_dat,cm->scale);
  }
}
  
int main(int argc, char *argv[]){
  char* filename;
  cm = Common::GetInstance();
  if (argc == 2) {
    filename = argv[1];

  } else {
    cout << "Enter the name of the input file:" << endl;
    cin >> filename;
  }
  init(filename);
int dataNum = cm->data.getDataNum()
  step();
  vector<BINARY2> binlist(Motion::GetInstance()->GetBinary_List());
  map<string,BINARY>bo_map(Motion_original::GetInstance()->GetBinaryList());
  vector<BINARY2>::iterator binit = binlist.begin();
  map<int,double> check_map;
  while(binit != binlist.end()){
    // printf("id[0] %d id[1] %d\n",(*binit).id[0],(*binit).id[1]);
    int id;
    id = min(id[0],id[1])*dataNum + max(id[0],id[1]);
    check_map.insert(pair<int,double>(id,(*binit).))
    binit++;
  }
  map<string,BINARY>::iterator bo_it = bo_map.begin();
  printf("\n");
  while(bo_it!=bo_map.end()){
    printf("id[0] %d id[1] %d\n",(*bo_it).second.id[0],(*bo_it).second.id[1]);
    bo_it++;
  }
  printf("size %d\n",binlist.size());
  printf("orn size %d\n",bo_map.size());
  return 0;
}
