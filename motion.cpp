#include "motion.h"

void Motion::bin_map_initialize(){
  map<string,BINARY2>::iterator it;
  it = bin_map.begin();
  while(it != bin_map.end()){
    (*it).second.tag = false;
    it++;
  }
}

void Motion::FindBinary_initialize(){
  bin_map_initialize();
  binary_list.clear();
}

void Motion::bin_map_erase(){
  map<string,BINARY2>::iterator it;
  it = bin_map.begin();
  while(it != bin_map.end()){
    if((*it).second.tag == false){
      bin_map.erase(it++);
    }else{
      ++it;
    }
  }
}

void Motion::Grid_decomp(double half_length,double cell_length,multimap<string,PARTICLE_INF>& cell_data){

  Common *cm = Common::GetInstance();
  vector<PARTICLE_INF>poslistV(cm->data.getCurrentPosInf());
  int x,y,z;
  char idstr[100];
  string name;
  for(int i=0;i<poslistV.size();i++){
    x =(int)(poslistV[i].pos.pos[0]/cell_length);
    y =(int)(poslistV[i].pos.pos[1]/cell_length);
    z =(int)(poslistV[i].pos.pos[2]/cell_length);
    sprintf(idstr,"%d,%d,%d",x,y,z);
    name = idstr;
    cell_data.insert(pair<string,PARTICLE_INF>(name,poslistV[i]));
  }
}

void Motion::Find_io_CellBinary(multimap<string,PARTICLE_INF>&cell_data,GLdouble scale,I_OR_O I_O,string iname,string tname){
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
  multimap<string,PARTICLE_INF>::iterator i_it = cell_data.lower_bound(iname);
  multimap<string,PARTICLE_INF>::iterator t_it;
  for(;i_it!=cell_data.upper_bound(iname);i_it++){
    if(I_O==I_TARGET){
      t_it = i_it;
      t_it++; 
    }else{
      t_it = cell_data.lower_bound(tname);
    }
    for(;t_it!=cell_data.upper_bound(tname);t_it++){
      id[0] = (*i_it).second.id;
      id[1] = (*t_it).second.id;
      pos[0] = (*i_it).second.pos;
      pos[1] = (*t_it).second.pos;
      sprintf(idstr,"%d,%d",id[0],id[1]);
      name = idstr;
      dist = cm->GetParticleDist(&pos[0],&pos[1]);
      if(dist <= DIST_THRESH2/scale2){
	BINARY2 binary2;
	binary2.id[0] = id[0];
	binary2.id[1] = id[1];
	binary2.pos[0] = pos[0];
	binary2.pos[1] = pos[1];
	GetCOM(pos,&(binary2.com),2);
	binary2.vel[0] = (*i_it).second.vel;
	binary2.vel[1] = (*t_it).second.vel;
	binary2.tag = true;
	binary2.dist = dist;
	map<string,BINARY2>::iterator it = bin_map.find(name);
	if(it != bin_map.end()){
	  binary2.count = (*it).second.count + 1;
	  (*it).second = binary2;
	}else{
	  binary2.count = 1;
	  bin_map.insert( pair<string, BINARY2>( name, binary2 ) );
	}
      }
    }
  }
}

void Motion::bin_map_to_binary_list(){
  map<string,BINARY2 >::iterator it;
  it = bin_map.begin();
  while(it != bin_map.end()){
    binary_list.push_back((*it).second);
    it++;
  }
}

void Motion::FindBinary(GLdouble tcur,GLdouble scale,double half_length){
  int max_index;
  double cell_length = CELL_LENGTH / scale;
  multimap<string,PARTICLE_INF> cell_data;
  FindBinary_initialize();
  Grid_decomp(half_length,cell_length,cell_data);
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
	    Find_io_CellBinary(cell_data,scale,I_TARGET,iname,iname);
	    int num = cell_data.count(iname);
	    for(int l=0;l <num;l++){
	      it++;
	    }
	  }else{
	    sprintf(idstr,"%d,%d,%d",i,j,k);
	    name = idstr;
	    Find_io_CellBinary(cell_data,scale,OTHER_TARGET,iname,name);
	  }
	}
      }
    }
    cell_data.erase(iname);
  }
  bin_map_erase();
  bin_map_to_binary_list();
}

void Motion::FindBinary(GLdouble tcur,GLdouble scale)
{

  Common *cm = Common::GetInstance();
  vector<PARTICLE_INF>poslistV = cm->data.getCurrentPosInf();
  char idstr[32];
  int i,j;
  int id1,id2;
  PARTICLE_POS pos[2];
  string name;
  for(i=0;i<poslistV.size();i++){
    pos[0]=poslistV[i].pos;
    id1 = poslistV[i].id;
    for(j=i+1;j<poslistV.size();j++){
      pos[1]=poslistV[j].pos;
      id2 = poslistV[j].id;
      sprintf(idstr,"%d,%d",id1,id2);
      name = idstr;
      double dist = cm->GetParticleDist(&pos[0],&pos[1]);
      if(dist <= DIST_THRESH/scale){
	if(binlist.find(name)==binlist.end()){
	  BINARY init = BINARY_INIT;
	  binlist[name]=init;
	  binlist[name].id[0] = id1;
	  binlist[name].id[1] = id2;
	}
	binlist[name].vel[0] = poslistV[i].vel;
	binlist[name].vel[1] = poslistV[j].vel;
	for(int k=0;k<2;k++){
	  binlist[name].pos[k] = pos[k];
	}
	GetCOM(pos,&(binlist[name].com),2);
	if(binlist[name].count < 30){
	  binlist[name].count++;
	}
      }else{
	if(binlist.find(name)!=binlist.end()){
	  binlist.erase(name);
	}
      }
    }
  }
  return;
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

