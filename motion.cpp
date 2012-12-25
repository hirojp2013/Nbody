#include "motion.h"

void Motion::init(void)
{
  box_initialize(200);
}



void Motion::box_initialize(int max_index){
  this->cell_data.resize(max_index);
  for(int i=0;i<max_index;i++){
    this->cell_data[i].resize(max_index);
    for(int j=0;j<max_index;j++){
      this->cell_data[i][j].resize(max_index);
    }
  }
}
void Motion::bin_map_initialize(){
  map<string,BINARY2>::iterator it;
  it = bin_map.begin();
  while(it != bin_map.end()){
    (*it).second.tag = false;
    it++;
  }
}

void Motion::FindBinary_initialize(){
  //  box_initialize(cell_data,max_index);
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  bin_map_initialize();
  binary_list.clear();
  key_list.clear();
}

bool Motion::isInBox(int x,int y,int z,int max_index){
  if(x>=0&&y>=0&&z>=0&&
     x<=max_index&&
     y<=max_index&&
     z<=max_index){
    return true;
  }else{
    return false;
  }
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

void Motion::Grid_decomp(double half_length,double cell_length){

  Common *cm = Common::GetInstance();
  vector<PARTICLE_INF>poslistV(cm->data.getCurrentPosInf());
  POS_KEY key;
  for(int i=0;i<poslistV.size();i++){
    key.x =(int)(poslistV[i].pos.pos[0]+half_length)/cell_length;
    key.y =(int)(poslistV[i].pos.pos[1]+half_length)/cell_length;
    key.z =(int)(poslistV[i].pos.pos[2]+half_length)/cell_length;
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    //    printf("cell_length %f\n",cell_length);
    //    printf("cell_data %d ,key.x %d key.y %d key.z %d\n",cell_data.size(),key.x,key.y,key.z);
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    cell_data[key.x][key.y][key.z].push_back(poslistV[i]);
    //    printf("%s(%d)\n",__FILE__,__LINE__);

    //    printf("%s(%d)\n",__FILE__,__LINE__);
    key_list.push_back(key);
  }
}

void Motion::Find_io_CellBinary(vector<PARTICLE_INF>& ilist,vector<PARTICLE_INF>& target_list,
				double scale,I_OR_O I_O){
  int id[2];
  char idstr[32];
  string name;
  PARTICLE_POS pos[2];
  PARTICLE_POS com;
  PARTICLE_VEL vel[2];
  double dist;
  int count;
  Common *cm = Common::GetInstance();
  for(int i=0;i<ilist.size();i++){
    int j;
    if(I_O==I_TARGET){
      j=i+1;
    }else{
      j=0; 
    }
    for( ;j<target_list.size();j++){
      id[0] = ilist[i].id;
      id[1] = ilist[j].id;
      pos[0] = ilist[i].pos;
      pos[1] = ilist[j].pos;
      sprintf(idstr,"%d,%d",id[0],id[1]);
      name = idstr;
      dist = cm->GetParticleDist(&pos[0],&pos[1]);
      if(dist <= DIST_THRESH/scale){
	BINARY2 binary2;
	binary2.id[0] = id[0];
	binary2.id[1] = id[1];
	GetCOM(pos,&(binary2.com),2);
	binary2.vel[0] = ilist[i].vel;
	binary2.vel[1] = ilist[j].vel;
	map<string,BINARY2>::iterator it = bin_map.find(name);
	binary2.tag = true;
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
  if(I_O==I_TARGET){
    target_list.clear();
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

void Motion::FindBinary(double tcur,double scale,double half_length){

  int max_index;
  double cell_length = CELL_LENGTH / scale;
  max_index = 2*(int)(half_length/cell_length) + 1;
  FindBinary_initialize();
  Grid_decomp(half_length,cell_length);
  vector<POS_KEY>::iterator it = key_list.begin();
  while(it!=key_list.end()){
    int ix,iy,iz;
    ix = (*it).x;iy = (*it).y;iz = (*it).z;
    vector<PARTICLE_INF>&ilist = cell_data[ix][iy][iz];
    for(int i=ix-1;i<=ix+1;i++){
      for(int j=iy-1;j<=iy+1;j++){
	for(int k=iz-1;k<=iz+1;k++){
	  if(i==ix&&j==iy&&k==iz){
	    Find_io_CellBinary(ilist,ilist,scale,I_TARGET);
	  }else{
	    if(isInBox(i,j,k,1000)){
	      vector<PARTICLE_INF>& target_list = cell_data[i][j][k];
	      Find_io_CellBinary(ilist,target_list,scale,OTHER_TARGET);
	    }
	  }
	}
      }
    }
    it++;
  }

  
  map<string,BINARY2>::iterator binmap_it = bin_map.begin();
  //  printf("\n");
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  while(binmap_it!=bin_map.end()){
    //    printf("pos[0] %d pos[1] %d\n",(*binmap_it).second.pos[0],(*binmap_it).second.pos[1]);
    binmap_it++;
  }

  bin_map_erase();
  bin_map_to_binary_list();
  //  printf("\n");
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  vector<BINARY2>::iterator binit = binary_list.begin();
  while(binit != binary_list.end()){
    //   printf("pos[0] %d pos[1] %d\n",(*binit).pos[0],(*binit).pos[1]);
    binit++;
  }

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

