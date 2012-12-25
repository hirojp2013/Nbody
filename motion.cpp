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



void Motion::Grid_decomp(double cell_length){

  Common *cm = Common::GetInstance();
  vector<PARTICLE_INF>poslistV(cm->data.getCurrentPosInf());
  int x,y,z;
  int max_num;
  CELL *cell_adress; 
  for(int i=0;i<poslistV.size();i++){
    x =(int)(floor)(poslistV[i].pos.pos[0]/cell_length);
    y =(int)(floor)(poslistV[i].pos.pos[1]/cell_length);
    z =(int)(floor)(poslistV[i].pos.pos[2]/cell_length);

    if(x>=MAX_INDEX){
      x = MAX_INDEX-1;
    }
    if(y>=MAX_INDEX){
      y = MAX_INDEX-1;
    }
    if(z>=MAX_INDEX){
      z = MAX_INDEX-1;
    }
    cell_adress = *(cell_data[x][y][z]);
    max_num =cell_adress->par_num_per_cell;
    cell_adress.par_inf_list[max_num] = poslistV[i];
    cell_adress-> par_num_per_cell++;
    pos_key_list[bi_num].x=x;
    pos_key_list[bi_num].y=y;
    pos_key_list[bi_num].z=z;
    bi_num++;
  }
}

int get_hist_len(int min_id,int max_id){
  for(int i=0;i<history[min_id].n_coutpt;i++){
    if(history[min_id].coutpt_id[i] == max_id){
      return hist_list[i];
    }
  }
  return 0;
}

void Motion::delete_cell(POS_KEY ikey){
cell_data
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
  double thresh_hold_scale = DIST_THRESH2 / scale2;
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


void Motion::Find_I_CellBinary(GLdouble scale,POS_KEY ikey){
  int id[2];
  PARTICLE_POS pos[2];
  PARTICLE_POS com;
  PARTICLE_VEL vel[2];
  double dist;
  BINARY binary;
  int count;
  Common *cm = Common::GetInstance();
  double scale2 = scale * scale;
  double thresh_hold_scale = DIST_THRESH2 / scale2;
  CELL icell = cell_data[ikey.x][ikey.y][ikey.z];
  for(int i=0;i<icell.par_num_per_cell;i++){
    for(int j=i+1;j<icell.par_num_per_cell;j++){
      pos[0] = icell.par_inf_list[i].pos;
      pos[1] = icell.par_inf_list[j].pos;
      dist = cm->GetParticleDist(&pos[0],&pos[1]);
      if(dist <= thresh_hold_scale){
	id[0] = (*i_it).second.id;
	id[1] = (*t_it).second.id;
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
	binary.count = get_hist_len(min(id0,id1),max(id0,id1))+1;
	binlist[bi_num] = binary;
	bi_num++;
      }
    }
  }
}




void Motion::FindBinary(GLdouble tcur,GLdouble scale){
  double cell_length = CELL_LENGTH / scale;
  FindBinary_initialize();
  Grid_decomp(cell_length);
  /*
 *** You must zeroset bi_num here.
 *** You will use bi_num below this line.
 */
  bi_num=0;
  for(int i=0;i<bi_num;i++){
    POS_KEY ikey;
    ikey.x = pos_key_vec[i].x;
    ikey.y = pos_key_vec[i].y;
    ikey.z = pos_key_vec[i].z;
    for(int i=ix-1;i<=ix+1;i++){
      for(int j=iy-1;j<=iy+1;j++){
	for(int k=iz-1;k<=iz+1;k++){
	  if(i==ix&&j==iy&&k==iz){
	    Find_I_CellBinary(scale,ikey);
	    delete_cell(ikey);
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

