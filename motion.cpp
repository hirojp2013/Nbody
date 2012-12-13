#include "motion.h"

void Motion::init(void)
{
  //  box_initialize(200);
}


/*
void Motion::box_initialize(int max_index){
  this->cell_data.resize(max_index);
  for(int i=0;i<max_index;i++){
    this->cell_data[i].resize(max_index);
    for(int j=0;j<max_index;j++){
      this->cell_data[i][j].resize(max_index);
    }
  }
}
*/

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
/*
void Motion::box_clear(){
  for(int i=0;i<200;i++){
    for(int j=0;j<200;j++){
      for(int k=0;k<200;k++){
	cell_data[i][j][k].clear();
      }
    }
  }
}
*/
void Motion::Grid_decomp(double half_length,double cell_length,multimap<string,PARTICLE_INF>& cell_data){

  Common *cm = Common::GetInstance();
  vector<PARTICLE_INF>poslistV(cm->data.getCurrentPosInf());
  int x,y,z;
  char idstr[100];
  string name;
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",cell_length);
  for(int i=0;i<poslistV.size();i++){
    x =(int)(poslistV[i].pos.pos[0]/cell_length);
     //   printf("%f %d\n",poslistV[i].pos.pos[0]/cell_length,x);
     y =(int)(poslistV[i].pos.pos[1]/cell_length);
     z =(int)(poslistV[i].pos.pos[2]/cell_length);
     //     printf("%s(%d)\n",__FILE__,__LINE__);
     //     printf("x %d y %d z %d\n",x,y,z);
     //     printf("%s(%d)\n",__FILE__,__LINE__);
    sprintf(idstr,"%d,%d,%d",x,y,z);
    name = idstr;
    cell_data.insert(pair<string,PARTICLE_INF>(name,poslistV[i]));
  }
}

void Motion::Find_io_CellBinary(multimap<string,PARTICLE_INF>&cell_data,GLdouble scale,I_OR_O I_O,string iname,string tname){

  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("I_O %d,isize %d tsize %d\n",I_O,ilist.size(),target_list.size());
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  
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
    //      printf("%s(%d)\n",__FILE__,__LINE__);
    //      printf("j %d target_list.size() %d\n",j,target_list.size());
    //      printf("%s(%d)\n",__FILE__,__LINE__);
    for(;t_it!=cell_data.upper_bound(tname);t_it++){
//      id[0] = ilist[i].id;
      id[0] = (*i_it).second.id;
      //      id[1] = target_list[j].id;
      id[1] = (*t_it).second.id;
      //      pos[0] = ilist[i].pos;
      pos[0] = (*i_it).second.pos;
      pos[1] = (*t_it).second.pos;

      if(iname == "-1,2,-4"&&tname=="0,2,-3"){
	dist = cm->GetParticleDist(&pos[0],&pos[1]);
	printf("dist %f\n",dist);
      }
      sprintf(idstr,"%d,%d",id[0],id[1]);
      name = idstr;
      dist = cm->GetParticleDist(&pos[0],&pos[1]);
      //      printf("%s(%d)\n",__FILE__,__LINE__);
      //      printf("pos[0].x %f,pos[0].y %f,pos[0].z %f\n",pos[0].pos[0],pos[0].pos[1],pos[0].pos[2]);
      //      printf("pos[1].x %f,pos[1].y %f,pos[1].z %f\n",pos[1].pos[1],pos[1].pos[1],pos[1].pos[2]);
      //      printf("dist %f DIST_TRHESH2%f\n",dist,DIST_THRESH2/scale2);
      //      printf("%s(%d)\n",__FILE__,__LINE__);

        if(dist <= DIST_THRESH2/(scale2)){
      //      if(dist <= DIST_THRESH / scale){

	//	printf("%s(%d)\n",__FILE__,__LINE__);
	//	cout << "pos" << endl;
	//	cout << pos[0].pos[0] << " " << pos[0].pos[1] << " "<<pos[0].pos[2]<<endl ;
	
	//	printf("I_O %d id0 %d,id1 %d\n",I_O,id[0],id[1]);
	//	std::cout << "iname " << iname << "tname "<<tname << std::endl ;
	BINARY2 binary2;
	binary2.id[0] = id[0];
	binary2.id[1] = id[1];
	binary2.pos[0] = pos[0];
	binary2.pos[1] = pos[1];
	GetCOM(pos,&(binary2.com),2);
	//	binary2.vel[0] = ilist[i].vel;
	binary2.vel[0] = (*i_it).second.vel;
	//	binary2.vel[1] = target_list[j].vel;
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
  //  printf("%s(%d)\n\n",__FILE__,__LINE__);
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
  //  max_index = 2*(int)(half_length/cell_length) + 1;
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
    vector<PARTICLE_INF>ilist;
    multimap<string,PARTICLE_INF>::iterator tenit = cell_data.lower_bound(iname);
    while(tenit!=cell_data.upper_bound(iname)){
      ilist.push_back((*tenit).second);
      tenit++;
    }
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

	    //	    printf("%s(%d)\n",__FILE__,__LINE__);
	  }else{
	    sprintf(idstr,"%d,%d,%d",i,j,k);
	    name = idstr;
	    if(ix == -1&&iy==2&&iz == -4){
	      if(i == 0&& j == 2 && k == -3){
		printf("%s(%d)\n",__FILE__,__LINE__);
	      printf("x %d,y %d z %d\n",i,j,k);
	      printf("count %d\n",cell_data.count("0,2,-3"));
	      cout <<(*cell_data.find("0,2,-3")).second.pos.pos[0]
		   <<(*cell_data.find("0,2,-3")).second.pos.pos[1]
		   <<(*cell_data.find("0,2,-3")).second.pos.pos[2] << endl;
	      cout << iname << " "<< name << endl;
	      }
	    }
	  
	    vector<PARTICLE_INF> target_list;
	    tenit = cell_data.lower_bound(name);
	    if(tenit != cell_data.upper_bound(name)){
	      while(tenit!=cell_data.upper_bound(name)){
		target_list.push_back((*tenit).second);
		tenit++;
	      }
	      Find_io_CellBinary(cell_data,scale,OTHER_TARGET,iname,name);
	    }
	  }
	}
      }
      
    }
    cell_data.erase(iname);
  }
  bin_map_erase();
  bin_map_to_binary_list();
  /*
  printf("binary_list_size %d\n",binary_list.size());
  
  printf("%s(%d)\n",__FILE__,__LINE__);
  vector<BINARY2>::iterator bit = binary_list.begin();

  while(bit != binary_list.end()){
    double x,y,z,x2,y2,z2;
    x =(*bit).pos[0].pos[0];
    y =(*bit).pos[0].pos[1];
    z =(*bit).pos[0].pos[2];
    x2 =(*bit).pos[1].pos[0];
    y2 =(*bit).pos[1].pos[1];
    z2 =(*bit).pos[1].pos[2];

    int x_t,y_t,z_t,x_t2,y_t2,z_t2;
    x_t = (int)(x/DIST_THRESH/scale);
    y_t = (int)(y/DIST_THRESH/scale);
    z_t = (int)(z/DIST_THRESH/scale);
    x_t2 = (int)(x2/DIST_THRESH/scale);
    y_t2 = (int)(y2/DIST_THRESH/scale);
    z_t2 = (int)(z2/DIST_THRESH/scale);
    printf("scale %f\n",scale);
   cout <<x_t<<" "<<y_t <<" "<<z_t<<endl; 
   cout <<x_t2<<" "<<y_t2 <<" "<<z_t2<<endl; 
   cout << "pos" << endl;
   cout << x << " "<<y<<" "<<z<<endl ;
   cout << x2 << " "<<y2<<" "<<z2<<endl ;
    cout << "com" << endl;
    cout << (*bit).com.pos[0] << " "<<(*bit).com.pos[1] << " " << (*bit).com.pos[2] << endl;
    cout << "count" << endl;
    cout << (*bit).count << endl;
    bit++;
  }
  */
  
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

