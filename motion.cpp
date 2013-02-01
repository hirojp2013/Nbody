#include "motion.h"
#include "common.h"

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

void Motion::Grid_decomp(multimap<string,PARTICLE_INF>& cell_data,double cell_length){

  Common *cm = Common::GetInstance();
  vector<PARTICLE_INF>poslistV(cm->data.getCurrentPosInf());
  int x,y,z;
  char idstr[100];
  string name;
  for(int i=0;i<poslistV.size();i++){
    x =(int)(floor)(poslistV[i].pos.pos[0]/cell_length);
    y =(int)(floor)(poslistV[i].pos.pos[1]/cell_length);
    z =(int)(floor)(poslistV[i].pos.pos[2]/cell_length);
    sprintf(idstr,"%d,%d,%d",x,y,z);
    name = idstr;
    cell_data.insert(pair<string,PARTICLE_INF>(name,poslistV[i]));
  }
}

void Motion::Find_io_CellBinary(multimap<string,PARTICLE_INF>&cell_data,GLdouble scale,I_OR_O I_O,string iname,string tname,vector<PARTICLE_INF>& poslistV){
  int id[2];
  char idstr[32];
  string name;
  PARTICLE_POS pos[2];
  PARTICLE_POS com;
  PARTICLE_VEL vel[2];
  double dist;
  BINARY binary;
  int count;
  Common *cm = Common::GetInstance();
  double scale2 = scale * scale;
  double thresh_hold_scale = DIST_THRESH2 / scale2;
  multimap<string,PARTICLE_INF>::iterator i_it = cell_data.lower_bound(iname);
  multimap<string,PARTICLE_INF>::iterator t_it;

  int index_i,index_t;
  double kin;
  Particle pt;
  for(;i_it!=cell_data.upper_bound(iname);i_it++){
    index_i = (*i_it).second.id-1;
    pos[0] = (*i_it).second.pos;
    if(I_O==I_TARGET){
      poslistV[index_i].id = (*i_it).second.id;
      poslistV[index_i].pos =(*i_it).second.pos;
      poslistV[index_i].vel =(*i_it).second.vel;
      pt.getKin(&kin,(*i_it).second.vel.vel,cm->scale);
      poslistV[index_i].kin = kin;

      t_it = i_it;
      t_it++; 
    }else{
      t_it = cell_data.lower_bound(tname);
    }
    for(;t_it!=cell_data.upper_bound(tname);t_it++){
      pos[1] = (*t_it).second.pos;
      dist = cm->GetParticleDist(&pos[0],&pos[1]);

      if(dist <= thresh_hold_scale){
 	id[0] = (*i_it).second.id;
	id[1] = (*t_it).second.id;
 	sprintf(idstr,"%d,%d",id[0],id[1]);
 	name = idstr;
 	BINARY binary;
 	binary.id[0] = id[0];
 	binary.id[1] = id[1];
 	binary.pos[0] = pos[0];
 	binary.pos[1] = pos[1];
 	GetCOM(pos,&(binary.com),2);
 	binary.vel[0] = (*i_it).second.vel;
 	binary.vel[1] = (*t_it).second.vel;
 	binary.tag = true;
 	binary.dist = dist;
	if(cm->binary_state == AROUND){
	  index_t = (*t_it).second.id-1;
	  poslistV[index_i].pot = poslistV[index_i].pot + ( 1.0/sqrt(dist) );
	  poslistV[index_t].pot = poslistV[index_t].pot + ( 1.0/sqrt(dist));
	}else if(cm->binary_state == NEARBY 
		 || cm->binary_state == ENG_SUM){
	  if(sqrt(dist) < poslistV[index_i].l){
	    if(cm->binary_state == NEARBY){
	      poslistV[index_i].l = sqrt(dist);
	    }
	    else{
	      pt.getKin(&kin,(*t_it).second.vel.vel,cm->scale);
	      poslistV[index_i].eng_sum = poslistV[index_i].kin+kin
		-1.0/poslistV[index_i].l;
	    }
	  }
	  
	  index_t = (*t_it).second.id-1;
	  if(sqrt(dist) < poslistV[index_t].l){
	    if(cm->binary_state== NEARBY){
	      poslistV[index_t].l = sqrt(dist);
	    }else{
	      pt.getKin(&kin,(*t_it).second.vel.vel,cm->scale);
	      poslistV[index_t].eng_sum = poslistV[index_i].kin+
		kin -1.0/poslistV[index_t].l;
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
  } 
}

void Motion::FindBinary(GLdouble tcur,GLdouble scale){
  double cell_length = CELL_LENGTH / scale;
  FindBinary_initialize();
  Grid_decomp(cell_data,cell_length);
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%d\n",cell_data.size());
  Common *cm = Common::GetInstance();
  vector<PARTICLE_INF>& poslistV = cm->GetInstance()->data.getCurrentPosInf();
  {
    poslistV.clear();
    PARTICLE_INF par_inf = PARTICLE_INF_INIT;
    poslistV.resize(cm->data.getIDNum(),par_inf);
  }
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%d",poslistV.size());
  multimap<string,PARTICLE_INF>::iterator it = cell_data.begin();
  char idstr[100];
  string name;
  string iname;
  it = cell_data.begin();
  while(it!=cell_data.end()){
    iname = (*it).first;
    int ix,iy,iz;
    sscanf(iname.c_str(),"%d,%d,%d",&ix,&iy,&iz);
    for(int i=ix-1;i<=ix+1;i++){
      for(int j=iy-1;j<=iy+1;j++){
	for(int k=iz-1;k<=iz+1;k++){
	  if(i==ix&&j==iy&&k==iz){
	    Find_io_CellBinary(cell_data,scale,I_TARGET,iname,iname,poslistV);
	    int num = cell_data.count(iname);
	    for(int l=0;l <num;l++){
	      it++;
	    }
	  }else{
	    sprintf(idstr,"%d,%d,%d",i,j,k);
	    name = idstr;
	    Find_io_CellBinary(cell_data,scale,OTHER_TARGET,iname,name,poslistV);
	  }
	}
      }
    }
    cell_data.erase(iname);
  }
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  bin_map_erase();
  //  printf("%s(%d)\n",__FILE__,__LINE__);
}

void Motion::GetCOM(PARTICLE_POS *pos, PARTICLE_POS *com, int num)
{
  for (int i= 0; i < 3; i++) {
    com->pos[i] = 0.0;
  }

  for (int i = 0; i < num; i++) {
    for (int j = 0; j < 3; j++) {
      com->pos[j] += pos[i].pos[j];
    }
  }

  for (int i = 0; i < 3; i++) {
    com->pos[i] /= num;
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

