#include "Particle.h"
#include<cmath>

Particle::Particle()
{
  init();
}

void Particle::init()
{
  id = -1;
  t = 0.0;
  vlen =  0.0;
  for (int i = 0; i < 3; i++) {
    x[i] = 0.0;
    v[i] = 0.0;
    a[i] = 0.0;
    j[i] = 0.0;
  }
}

bool Particle::isEmpty()
{
  return id < 0; 
}

void Particle::setData(string name, vector<double> &val)
{
  double *p = NULL;
  if (name == "x") {
    p = &x[0];
  } else if (name == "v") {
    p = &v[0];
  } else if (name == "a") {
    p = &a[0];
  } else if (name == "j") {
    p = &j[0];
  }
  if (p != NULL) {
    for (vector<double>::iterator it = val.begin(); it != val.end(); it++) {
      *p++ = *it;
    }
  }
  if (name == "v") {
    vlen = 0.0;
    for (int i = 0; i < 3; i++) {
      vlen += v[i] * v[i];
    }
    vlen = sqrt(vlen);
  }
}

void Particle::setId(int val) {
  id = val;
}

void Particle::setTime(double val) {
  t = val;
}

void Particle::setX(const double *pos) {
  for (int i = 0; i < 3; i++) {
    x[i] = pos[i];
  }
}

void Particle::getVlen2(double *vlen2,double scale){
  double tmp=0.0;
  double v_tmp;
  for(int i=0;i<3;i++){
    v_tmp = v[i]/scale;
    tmp += v_tmp*v_tmp;
  }
  *vlen2 = tmp;
}

void Particle::getVlen2(double *vlen2,double v[3],double scale){
  double tmp=0.0;
  double v_tmp;

  for(int i=0;i<3;i++){
    v_tmp = v[i]/scale;
    tmp += v_tmp*v_tmp;
  }
  // printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",tmp);

  *vlen2 = tmp;
}


void Particle::getKin(double *kin,double *v,double scale){
  Particle pt;
  double vlen2;
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f %f %f\n",v[0],v[1],v[2]);

  pt.getVlen2(&vlen2,v,scale);
  *kin = 0.5*vlen2;
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",*kin);

}


void Particle::extrapolate(double tcur, GLdouble scale, double *pos) {
  double dt = tcur - t;
  /*
  printf("%s(%d)\n",__FILE__,__LINE__);
  printf("tcur %f t %f\n",tcur, t);
  */
  for (int i = 0; i < 3; i++) {
    pos[i] = ( (a[i] * dt * 0.5 + v[i]) * dt + x[i] ) / scale;
  }
}

/*
 * readData
 *   read particle data file in YAML format (block style)
 */
bool ParticleData::readData(const char *filename)
{
  ifstream ifs(filename);
  if (!ifs) {
    //		cout << "ParticleData::readData(): can't open " << filename << "." << endl;
    return false; 
  }

  string buf;
  string key, val;
  Particle ptc;
  string::size_type pos;
  vector<double> dval;
  data.clear();
  int cnt = 0;
  while (getline(ifs, buf)) {

    if (buf.find("- ") == 0) {
      val = buf.substr(2);
      dval.push_back(atof(val.c_str()));
    } else {
      if (key != "") {
	if (dval.size() != 3) {
	  cout << "WARNING: incomplete data " << key << " (line " << (cnt - dval.size()) << ")" << endl;
	}
	ptc.setData(key, dval);
	dval.clear();
	key = "";
      }

      /*--- !!Particle*/
      if (buf.find("---") == 0) {  // delimiter of each particle

	if (!ptc.isEmpty()) {
	  data.push_back(ptc);
	}
	ptc.init();

      } else if ((pos = buf.find(": ")) != string::npos) {
	key = buf.substr(0, pos);
	val = buf.substr(pos + 2);
	if (val.length() == 0) {
	  dval.clear();
	} else {
	  if (key == "id") {
	    ptc.setId(atoi(val.c_str()));
	  } else if (key == "t") {
	    ptc.setTime(atof(val.c_str()));
	  }
	  key = "";
	}
      }
    }
    cnt++;
    //while roop terminated
  }

  if (!dval.empty()) {
    if (dval.size() != 3) {
      cout << "WARNING: incomplete data " << key << " (line " << (cnt - dval.size()) << ")" << endl;
    }
    ptc.setData(key, dval);
  }
  if (!ptc.isEmpty()) {
    data.push_back(ptc);
  }

  ifs.close();
  dataNum = data.size();
  cout << "Data length: " << dataNum << endl;

  vmax = 0.0;
  for (int i = 0; i < dataNum; i++) {
    if (data[i].getVLen() > vmax) {
      vmax = data[i].getVLen();
    }
  }
  return true;
}

int ParticleData::initList(void)
{
  int dataNum = data.size();

  // create particle list
  map<int, int> palist;
  for (int i = dataNum - 1; i >= 0; i--) {
    palist[data[i].id] = i;
  }
  id_num = palist.size();
  cout << "ID num: " << id_num << endl;
  map<int, int>::iterator p;
  vector<int> idlist;
  for (p = palist.begin(); p != palist.end(); p++) {
    idlist.push_back(p->first);
  }
  sort(idlist.begin(), idlist.end());
  curlist.assign(*(idlist.end() - 1) + 1, -1);
  int nframe = 0;
  for (int i = 0; i < dataNum; i++) {
    if (data[i].t > 0.0) {
      break;
    }
    setCurrentParticle(i);
    nframe++;
  }

  return nframe;
}

Particle *ParticleData::getData(int index)
{
  if (index < 0 || index >= data.size()) {
    return NULL;
  }
  return &(data[index]);
}


double ParticleData::setCurrentParticle(int frame)
{
  //	cout << "  setCurrentParticle id: " << data[frame].id << " t: " << data[frame].t 
  //	 << " frame_prev: " << curlist[data[frame].id];
  curlist[data[frame].id] = frame;
  //	cout << " frame: " << curlist[data[frame].id] << endl;
  return data[frame].t;
}

double ParticleData::getCurrentParticleId(int frame)
{
  return data[frame].id;
}

vector<PARTICLE_INF>& ParticleData::getCurrentPosInf(double cur_t,double scale,vector<int> &curlist){

  vector<int>::iterator p;
  PARTICLE_INF pos_inf;
  poslistV.clear();
  for (p = curlist.begin(); p != curlist.end(); p++) {
    if(*p<0){
      continue;
    }
    Particle *pt = this->getData(*p);
    pt->extrapolate(cur_t, scale, pos_inf.pos);
    pos_inf.id = pt->getId();
    pt->getV(pos_inf.vel,scale);
    pt->getVlen2(&(pos_inf.vlen2),scale);
    //    pt->getKin(&(pos_inf.kin),scale);
    //    pos_inf.l = NOT_MAKE_BINARY;
    poslistV.push_back(pos_inf);
  }
  return poslistV;
}
