#include "motion.h"
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

void Motion::Grid_decomp(boost::unordered_multimap<string,PARTICLE_INF>& cell_data,
			 double cell_length){

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

void Motion::Find_io_CellBinary(boost::unordered_multimap<string,PARTICLE_INF>&cell_data,
				GLdouble scale,I_OR_O I_O,string iname,string tname){
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
  pair< boost::unordered_multimap<string,PARTICLE_INF>::iterator,
    boost::unordered_multimap<string,PARTICLE_INF>::iterator > pair_it_i;
  pair_it_i = cell_data.equal_range(iname);

  boost::unordered_multimap<string,PARTICLE_INF>::iterator i_it;

  pair< boost::unordered_multimap<string,PARTICLE_INF>::iterator,
    boost::unordered_multimap<string,PARTICLE_INF>::iterator > pair_it_t;
  pair_it_t = cell_data.equal_range(tname);
  boost::unordered_multimap<string,PARTICLE_INF>::iterator t_it;
  boost::unordered_multimap<string,PARTICLE_INF>::iterator it;


  for(i_it = pair_it_i.first;
      i_it!=pair_it_i.second;
      i_it++){
    if(I_O==I_TARGET){
      t_it = i_it;
      t_it++; 
    }else{
      t_it = pair_it_t.first;
    }
    for(;t_it!=pair_it_t.second;t_it++){
      pos[0] = (*i_it).second.pos;
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

	map<string,BINARY>::iterator it = bin_map.find(name);
	if(it != bin_map.end()){
	  if(cm->runstate == 1){
	    binary.count = (*it).second.count + 1;
	  }else{
	    binary.count = (*it).second.count;
	  }

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
  boost::unordered_multimap<string,PARTICLE_INF> cell_data;
  FindBinary_initialize();
  Grid_decomp(cell_data,cell_length);
  boost::unordered_multimap<string,PARTICLE_INF>::iterator it = cell_data.begin();
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

