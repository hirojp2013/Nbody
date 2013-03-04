#include "motion.h"
#include "common.h"

Motion::Motion(){ DIST_THRESH = .1; COMDIFF_THRESH = 0; BIN_COUNT_THRESH = 0; BIN_REMOVE_COUNT_THRESH = 0;EPSIRON = DIST_THRESH/4.0; CELL_LENGTH = DIST_THRESH;
 DIST_THRESH2 = DIST_THRESH*DIST_THRESH;
 cm = Common::GetInstance();
}


void Motion::init(){
  bin_map.clear();
}

void Motion::bin_map_initialize(){
  map<string,BINARY>::iterator it;
  it = bin_map.begin();
  while(it != bin_map.end()){
    (*it).second.tag = false;
    it++;
  }
}

void Motion::FindBinary_initialize(){
  bin_map_initialize();
  cell_data.clear();
}

void Motion::bin_map_erase(){
  map<string,BINARY>::iterator it;
  it = bin_map.begin();
  while(it != bin_map.end()){
    if((*it).second.tag == false){
      bin_map.erase(it++);
    }else{
      ++it;
    }
  }
}


void Motion::Grid_decomp(multimap<string,PARTICLE_INF>& cell_data,
			 double cell_length){

  vector<PARTICLE_INF>poslistV(cm->data.getCurrentPosInf());
  int x,y,z;
  char idstr[100];
  string name;
  for(int i=0;i<poslistV.size();i++){
    x =(int)(floor)(poslistV[i].pos[0]/cell_length);
    y =(int)(floor)(poslistV[i].pos[1]/cell_length);
    z =(int)(floor)(poslistV[i].pos[2]/cell_length);
    sprintf(idstr,"%d,%d,%d",x,y,z);
    name = idstr;
    cell_data.insert(pair<string,PARTICLE_INF>(name,poslistV[i]));

  }

}


void Motion::Search_icell(multimap<string,PARTICLE_INF>&cell_data,GLdouble scale,string iname,string tname){

  int id[2];
  char idstr[32];
  string name;
  double pos[2][3];
  double com[3];
  double vel[2][3];
  double dist;
  BINARY binary;
  int count;
  double scale2 = scale * scale;
  double thresh_hold_scale = DIST_THRESH2 / scale2;
  multimap<string,PARTICLE_INF>::iterator i_it = cell_data.lower_bound(iname);
  multimap<string,PARTICLE_INF>::iterator t_it;

  vector<PARTICLE_INF> &poslistV=cm->GetInstance()->data.getCurrentPosInf();

  int index_i,index_t;
  double kin;
  Particle pt;
  for(;i_it!=cell_data.upper_bound(iname);i_it++){

    index_i = (*i_it).second.id-1;
    pos[0][0] = (*i_it).second.pos[0];
    pos[0][1] = (*i_it).second.pos[1];
    pos[0][2] = (*i_it).second.pos[2];

    poslistV[index_i].id = (*i_it).second.id;

    poslistV[index_i].pos[0] =(*i_it).second.pos[0];
    poslistV[index_i].pos[1] =(*i_it).second.pos[1];
    poslistV[index_i].pos[2] =(*i_it).second.pos[2];

    poslistV[index_i].vel[0] =(*i_it).second.vel[0];
    poslistV[index_i].vel[1] =(*i_it).second.vel[1];
    poslistV[index_i].vel[2] =(*i_it).second.vel[2];

    pt.getKin(&kin,(*i_it).second.vel,cm->scale);
    poslistV[index_i].kin = kin;
    t_it = i_it;
    t_it++; 

    for(;t_it!=cell_data.upper_bound(tname);t_it++){
      Make_binary((*i_it),(*t_it),scale);
    }
  } 
}



void Motion::Search_tcell(multimap<string,PARTICLE_INF>&cell_data,GLdouble scale,string iname,string tname){

  int id[2];
  char idstr[32];
  string name;
  double pos[2][3];
  double com[3];
  double vel[2][3];
  double dist;
  BINARY binary;
  int count;
  double scale2 = scale * scale;
  double thresh_hold_scale = DIST_THRESH2 / scale2;
  multimap<string,PARTICLE_INF>::iterator i_it = cell_data.lower_bound(iname);
  multimap<string,PARTICLE_INF>::iterator t_it;


  int index_i,index_t;
  double kin;
  Particle pt;
  for(;i_it!=cell_data.upper_bound(iname);i_it++){

    index_i = (*i_it).second.id-1;
    pos[0][0] = (*i_it).second.pos[0];
    pos[0][1] = (*i_it).second.pos[1];
    pos[0][2] = (*i_it).second.pos[2];

    t_it = cell_data.lower_bound(tname);

    for(;t_it!=cell_data.upper_bound(tname);t_it++){
      Make_binary((*i_it),(*t_it),scale);
    }
  } 
}

void Motion::Make_binary(pair<string,PARTICLE_INF> ipar,pair<string,PARTICLE_INF> tpar,GLdouble scale){
  int id[2];
  char idstr[32];
  string name;
  double pos[2][3];
  double com[3];
  double vel[2][3];
  double dist;
  BINARY binary;
  int count;

  double kin;
  Particle pt;

  vector<PARTICLE_INF> &poslistV=cm->GetInstance()->data.getCurrentPosInf();

  Common *cm = Common::GetInstance();
  double scale2 = scale * scale;
  double thresh_hold_scale = DIST_THRESH2 / scale2;



  pos[0][0] = ipar.second.pos[0];
  pos[0][1] = ipar.second.pos[1];
  pos[0][2] = ipar.second.pos[2];


  pos[1][0] = tpar.second.pos[0];
  pos[1][1] = tpar.second.pos[1];
  pos[1][2] = tpar.second.pos[2];

  int index_i = ipar.second.id-1;
  int index_t = tpar.second.id-1;

  dist = cm->GetParticleDist(pos[0],pos[1]);
  if(cm->binary_state == POTENTIAL){
    poslistV[index_i].pot = poslistV[index_i].pot + ( 1.0/sqrt(dist) );
    poslistV[index_t].pot = poslistV[index_t].pot + ( 1.0/sqrt(dist));
  }


  if(dist <= thresh_hold_scale){

    id[0] = min(ipar.second.id,tpar.second.id);
    id[1] = max(ipar.second.id,tpar.second.id);
    sprintf(idstr,"%d,%d",id[0],id[1]);
    name = idstr;
    BINARY binary;
    binary.id[0] = id[0];
    binary.id[1] = id[1];

    binary.pos[0][0] = pos[0][0];
    binary.pos[0][1] = pos[0][1];
    binary.pos[0][2] = pos[0][2];

    binary.pos[1][0] = pos[1][0];
    binary.pos[1][1] = pos[1][1];
    binary.pos[1][2] = pos[1][2];

    GetCOM(pos,binary.com,2);
    binary.vel[0][0] = ipar.second.vel[0];
    binary.vel[0][1] = ipar.second.vel[1];
    binary.vel[0][2] = ipar.second.vel[2];

    binary.vel[1][0] = tpar.second.vel[0];
    binary.vel[1][1] = tpar.second.vel[1];
    binary.vel[1][2] = tpar.second.vel[2];

    binary.tag = true;
    binary.dist = dist;
    if(cm->binary_state == KINETIC 
       || cm->binary_state == GRAVITATIONALLY_BOUND || cm->binary_state == POTENTIAL){
      if(sqrt(dist) < poslistV[index_i].l){
	poslistV[index_i].l = sqrt(dist);
	if(cm->binary_state == GRAVITATIONALLY_BOUND){
	  poslistV[index_i].l = sqrt(dist);
	  pt.getKin(&kin,tpar.second.vel,cm->scale);
	  poslistV[index_i].eng_sum = poslistV[index_i].kin+kin
	    -(ipar.second.vel[0] * tpar.second.vel[0]+
	      ipar.second.vel[1] * tpar.second.vel[1]+
	      ipar.second.vel[2] * tpar.second.vel[2])-1.0/poslistV[index_i].l;
	}
      }
	  
      index_t = tpar.second.id-1;
      if(sqrt(dist) < poslistV[index_t].l){
	poslistV[index_t].l = sqrt(dist);
	if(cm->binary_state == GRAVITATIONALLY_BOUND){
	  pt.getKin(&kin,tpar.second.vel,cm->scale);
	  poslistV[index_t].eng_sum = poslistV[index_i].kin+
	    kin -(ipar.second.vel[0] * tpar.second.vel[0]+
		  ipar.second.vel[1] * tpar.second.vel[1]+
		  ipar.second.vel[2] * tpar.second.vel[2])
	    -1.0/poslistV[index_t].l;
	}
      }
    }
    map<string,BINARY>::iterator it = bin_map.find(name);
    if(it != bin_map.end()){
      binary.count = (*it).second.count + 1;
      (*it).second = binary;
	  
    }else{
      binary.count = 1;
      bin_map.insert( pair<string, BINARY>( name, binary ) );
    }
	
  }
}



void Motion::FindBinary(GLdouble tcur,GLdouble scale){
  double cell_length = CELL_LENGTH / scale;
  FindBinary_initialize();

  {
    map<string,BINARY>::iterator it;
    int i_test = 75,t_test= 85;
    string namei,namet;
    char test_chari[100];
    char test_chart[100];
    sprintf(test_chari,"%d,%d",i_test,t_test);
    sprintf(test_chart,"%d,%d",t_test,i_test);
    namei = test_chari;
    namet = test_chart;
    if(bin_map.count(namei)){
      it = bin_map.find(namei);

    }else if(bin_map.count(namet)){
      it = bin_map.find(namet);
    }

  }


  Grid_decomp(cell_data,cell_length);

  multimap<string,PARTICLE_INF>::iterator it = cell_data.begin();
  
  char idstr[100];
  string name;
  string iname;
  it = cell_data.begin();
  while(it!=cell_data.end()){
    iname = (*it).first;
    int ix,iy,iz;
    sscanf(iname.c_str(),"%d,%d,%d",&ix,&iy,&iz);
    Search_icell(cell_data,scale,iname,iname);
    int num = cell_data.count(iname);
    for(int l=0;l <num;l++){
      it++;
    }
    for(int i=ix-1;i<=ix+1;i++){
      for(int j=iy-1;j<=iy+1;j++){
	for(int k=iz-1;k<=iz+1;k++){
	  if(i==ix&&j==iy&&k==iz){
	    continue;
	  }else{
	    sprintf(idstr,"%d,%d,%d",i,j,k);
	    name = idstr;
	    Search_tcell(cell_data,scale,iname,name);
	  }
	}
      }
    }
    cell_data.erase(iname);
  }

  bin_map_erase();
}

void Motion::GetCOM(double pos[][3], double *com, int num)
{
  for (int i= 0; i < 3; i++) {
    com[i] = 0.0;
  }

  for (int i = 0; i < num; i++) {
    for (int j = 0; j < 3; j++) {
      com[j] += pos[i][j];
    }
  }

  for (int i = 0; i < 3; i++) {
    com[i] /= num;
  }
}

double Motion::GetCOMDiff(Particle *pt[], double *com_prev, int num)
{
  double com[3] = { 0.0 };
  for (int i = 0; i < num; i++) {
    double x[3];
    pt[i]->getX(x);
    for (int j = 0; j < 3; j++) {
      com[j] += x[j];
    }
  }

  double len = 0.0;
  for (int j = 0; j < 3; j++) {
    com[j] /= num;
    double diff = com[j] - com_prev[j];
    len += diff * diff;
  }
  return sqrt(len);
}

