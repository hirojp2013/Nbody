#include "common.h"


Common::Common()
{

  t_sys = 0.0;           // time
  interval = 0.005;
  frame = 0;             // frame number
  frame_max = 0;
  t_dat = 0.0;           // time (particle data)
  t_dat_max = 0.0; 
  frame_dat = 0;
  frame_dat_prev = -1;
  runstate = 0;          // status (0:stop  1:run)
  inc = 1;               // frame increment per step
  char_state = 1;        // Display the character
  is_acc = false;        // accelerate
  is_dec = false;        // decelerate
  scale = 1.0;           // scale of the system
  radius =10.0;         // particle radius
  theta =0.0;           // angle of rotation around z-axis
  phi = 0.0;             // angle of rotation around x-axis
  dx = 0.0;              // target position x (gluLookAt)
  dy = 0.0;              // target position y (gluLookAt)
  dd = 0.01;             // unit of movement of the target position

  beam_flag = false;
  rot = 0.0;
  vmax =  4.0;

};

Common::~Common()
{
}

double Common::GetParticleDist(PARTICLE_POS *p1, PARTICLE_POS *p2)
{


  double dist = 0.0;
  for (int i = 0; i < 3; i++) {
    dist += (p1->pos[i] - p2->pos[i]) * (p1->pos[i] - p2->pos[i]);
  }

  return dist;
}

void Common::clearTraj(){
  while(!traj.empty()){
    traj.pop();
  }

}

void Common::clearId(){
  while(!target_id.empty()){

    target_id.pop();
  }
}

void Common::allClear(){
  clearTraj();
  clearId();
}

void Common::coordtrans(float *orig_pos,float *dis_pos,float rot)
{
  double rad = rot*M_PI/180.0;
  dis_pos[0] = orig_pos[0] * cos(rad) - orig_pos[2] * sin(rad);
  dis_pos[1] = orig_pos[1];
  dis_pos[2] = orig_pos[0] * sin(rad) + orig_pos[2] * cos(rad);
}

void Common::SelectParticle()
{
 
  //	cout << "----------------------" << endl;
  //	cout << "SelectParticle: r: " << r << endl;
  vector<int> curlist = data.getCurrentList();
  vector<int>::iterator p;
  Particle candPt;
  double candPtDist = TARGET_DIST_THRESH/scale;
  float wandpos_tmp1[3],wandpos_tmp2[3];
  float wandvec_tmp1[3],wandvec_tmp2[3];
  PARTICLE_POS candPos;
  PARTICLE_POS crossPos;
  for(int i=0;i<3;i++){
    candPos.pos[i] = -100;
  }
  for (int i = 0; i < 3; i++) {
    wandpos_tmp1[i] -= (float) ORIG[i];
  }
  coordtrans(wandpos_tmp1,wandpos_tmp2,rot);
  coordtrans(wandvec_tmp1,wandvec_tmp2,rot);
  for (p = curlist.begin(); p != curlist.end(); p++) {
    PARTICLE_POS pos;
    double dist;

    if (*p < 0) {
      continue;
    }
    Particle *pt = data.getData(*p);
    pt->extrapolate(t_dat,scale,&pos);

    for (int i = 0; i < 3; i++) {
      crossPos.pos[i] = wandpos_tmp2[i]+(BEAM_SCALE*wandvec_tmp2[i]);
    }
    dist = GetParticleDist(&pos,&crossPos);
    if(dist < TARGET_DIST_THRESH/scale&&dist < candPtDist){
      candPt = *pt; 
      for(int i=0;i<3;i++){
	candPos.pos[i] = pos.pos[i];
      }
    }
  }
  if(candPt.getId()==-1){
    return;
  }	   

  if(target_id.empty()||
     (target_id.front()!=candPt.getId()&&target_id.back()!=candPt.getId())){
    target_id.push(candPt.getId());
    vector<TARGET_POS> pos_vector;
    traj.push(pos_vector);
  }
  if(target_id.size()==3
     ||(target_id.size()==2&&target_id.front()==target_id.back())
     ){
    target_id.pop();
    traj.pop();
  }
  return;
}


