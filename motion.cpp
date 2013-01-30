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

  PARTICLE_INF par_infi,par_inft;
  for(;i_it!=cell_data.upper_bound(iname);i_it++){
    pos[0] = (*i_it).second.pos;
    
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    //    printf("%f %f %f\n",par_inf.vel.vel[0],par_inf.vel.vel[1],par_inf.vel.vel[2]);
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    //    printf("%f\n",par_inf.kin);

    if(I_O==I_TARGET){
      poslistV[(*i_it).second.id].id = (*i_it).second.id;
      poslistV[(*i_it).second.id].pos =(*i_it).second.pos;
      poslistV[(*i_it).second.id].vel =(*i_it).second.vel;
      double kin;
      Particle pt;
      pt.getKin(&kin,(*i_it).second.vel.vel,cm->scale);
      poslistV[(*i_it).second.id].kin = kin;
      //      poslistV[(*i_it).second.id].l = 0.5;
      t_it = i_it;
      t_it++; 
    }else{
      t_it = cell_data.lower_bound(tname);
    }
    for(;t_it!=cell_data.upper_bound(tname);t_it++){
      pos[1] = (*t_it).second.pos;
      dist = cm->GetParticleDist(&pos[0],&pos[1]);
      if(dist <= thresh_hold_scale){
	printf("%s(%d)\n",__FILE__,__LINE__);
	//(*i_it).second.l = min((*i_it).second.l,sqrt(dist));
	//(*t_it).second.l = min((*t_it).second.l,sqrt(dist));
	par_infi.id = id[0] = (*i_it).second.id;
	par_inft.id = id[1] = (*t_it).second.id;
	sprintf(idstr,"%d,%d",id[0],id[1]);
	name = idstr;
	BINARY binary;
	binary.id[0] = id[0];
	binary.id[1] = id[1];
	binary.pos[0] = pos[0];
	
	par_inft.pos = binary.pos[1] = pos[1];
	GetCOM(pos,&(binary.com),2);
	binary.vel[0] = (*i_it).second.vel;
	
	par_inft.vel=binary.vel[1] = (*t_it).second.vel;
	binary.tag = true;
	binary.dist = dist;

	//	printf("%f\n",sqrt(dist));
	//par_inf.l = min(par_inf.l,sqrt(dist));
	Particle pt;

	//	pt.getKin(&(par_inft.kin),par_inft.vel.vel,cm->scale);
	if(sqrt(dist) < poslistV[par_infi.id].l){
	  printf("%s(%d)\n",__FILE__,__LINE__);
	  par_infi.l = sqrt(dist);
	  printf("%s(%d)\n",__FILE__,__LINE__);
	  printf("%f\n",par_infi.l);
	  poslistV[par_infi.id].l = par_infi.l;
	  //	  exit(0);
	}
	printf("%s(%d)\n",__FILE__,__LINE__);
	if(sqrt(dist) < poslistV[par_inft.id].l){
	  printf("%s(%d)\n",__FILE__,__LINE__);
	  par_inft.l = sqrt(dist);
	  poslistV[par_inft.id].l = par_inft.l;
	  //	  exit(0);
	}
	printf("%s(%d)\n",__FILE__,__LINE__);
	map<string,BINARY>::iterator it = bin_map.find(name);
	if(it != bin_map.end()){
	  binary.count = (*it).second.count + 1;
	  (*it).second = binary;
	}else{
	  binary.count = 1;
	  bin_map.insert( pair<string, BINARY>( name, binary ) );
	}
	printf("%s(%d)\n",__FILE__,__LINE__);
      }
   	printf("%s(%d)\n",__FILE__,__LINE__);
    }
    //    poslistV.push_back(par_inf);
   	printf("%s(%d)\n",__FILE__,__LINE__);
  
  } 
  printf("%s(%d)\n",__FILE__,__LINE__);
}

void Motion::FindBinary(GLdouble tcur,GLdouble scale){
  double cell_length = CELL_LENGTH / scale;
  FindBinary_initialize();
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%d\n",cell_data.size());

  Grid_decomp(cell_data,cell_length);
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%d\n",cell_data.size());
  Common *cm = Common::GetInstance();
  vector<PARTICLE_INF>& poslistV = cm->GetInstance()->data.getCurrentPosInf();
  poslistV.clear();
  {
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
  printf("%s(%d)\n",__FILE__,__LINE__);
  bin_map_erase();
  printf("%s(%d)\n",__FILE__,__LINE__);
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

