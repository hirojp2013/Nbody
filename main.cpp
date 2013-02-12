#include "common.h"
#include "ui.h"
#include "motion.h"
#include "Particle.h"
#include "Particle_Objs.h"
#include<math.h>
#include<algorithm>
#include<cassert>

#include "common.h"
#include "binary.h"
#include "motion.h"
#include "ui.h"


#define TEXHEIGHT 64
#define TEXWIDTH 64
static const char texture[] = "ball.raw";



const GLfloat distance[] = { 0.0, 0.0, 1.0 };

static UI *ui = NULL;
static Common *cm = NULL;

static Particle_Objs *pobjs;  
double SCALE = 0.01;

static GLUquadricObj *sphereObj[CAVE_MAX_WALLS] = { NULL };
static GLUquadricObj *clyndObj[CAVE_MAX_WALLS] = {NULL};
static GLUquadricObj *discObj[CAVE_MAX_WALLS] = {NULL};

GLuint theBeam[CAVE_MAX_WALLS];
GLuint theArrow[CAVE_MAX_WALLS];


binary *bobj;


void the_beam(){

  glTranslated(0.0,0.0,-CROSS_LENGTH);
  gluCylinder(clyndObj[CAVEUniqueIndex()],BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  gluDisk(discObj[CAVEUniqueIndex()],0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);

  gluCylinder(clyndObj[CAVEUniqueIndex()],BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluDisk(discObj[CAVEUniqueIndex()],0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,-CROSS_LENGTH);
  glRotated(90,1.0,0.0,0.0);

  glTranslated(0.0,0.0,-CROSS_LENGTH);
  gluCylinder(clyndObj[CAVEUniqueIndex()],BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  gluDisk(discObj[CAVEUniqueIndex()],0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluCylinder(clyndObj[CAVEUniqueIndex()],BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluDisk(discObj[CAVEUniqueIndex()],0.0,BEAM_WIDTH,16,16);
		
  glTranslated(0.0,0.0,-CROSS_LENGTH);
  glRotated(90,1.0,0.0,0.0);

  glRotated(90,0.0,1.0,0.0);
  glTranslated(0.0,0.0,-CROSS_LENGTH);
  gluCylinder(clyndObj[CAVEUniqueIndex()],BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  gluDisk(discObj[CAVEUniqueIndex()],0.0,BEAM_WIDTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluCylinder(clyndObj[CAVEUniqueIndex()],BEAM_WIDTH,BEAM_WIDTH,CROSS_LENGTH,16,16);
  glTranslated(0.0,0.0,CROSS_LENGTH);
  gluDisk(discObj[CAVEUniqueIndex()],0.0,BEAM_WIDTH,16,16);
}


void init(void *filename)
{
  GLfloat light_position[] = { 0.0f, 30.0f, 50.0f, 0.0f };
  /*
 *** texture
 */

  static GLubyte image[TEXHEIGHT][TEXWIDTH][4];


  if (CAVEMasterDisplay()) {
    cm->display_num = CAVENumPipes();
    cout << "display_num: " << cm->display_num << endl;
    bool ret = cm->data.readData((const char *)filename);
    if (!ret) {
      cout << "Can't read the input data." << endl;
      exit(-1);
    }
    cm->t_dat_max = cm->data.getData(cm->data.getDataNum() - 1)->getTime();
    cm->frame_max = (int)(cm->t_dat_max / cm->interval) + 1;
    cm->frame_dat = cm->data.initList() - 1;
    cout << setprecision(15)
	 << "time_max: " << cm->t_dat_max
	 << " interval: " << cm->interval
	 << " frame_max: " << cm->frame_max
	 << " vmax: " << cm->vmax
	 << endl;
    cout << setprecision(15)
	 << "frame_dat: " << cm->frame_dat << " t_dat: " << cm->t_dat << endl;


    pobjs = new Particle_Objs;


	
#if 0
    printf("INPUT --------------------------------------------\n");
    for (int i = 0; i < cm->data.getDataNum(); i++) {
      double va[3], vj[3], vv[3], vx[3];
      Particle *p = cm->data.getData(i);
      printf("--- !!Particle \n");
      p->getA(va);
      printf("a: \n");
      for (int j = 0; j < 3; j++) {
	printf("- %.15g\n", va[j]);
      }
      printf("id: %d\n", p->getId());
      p->getJ(vj);
      printf("j: \n");
      for (int j = 0; j < 3; j++) {
	printf("- %.15g\n", vj[j]);
      }
      printf("t: %.15g\n", p->getTime());
      p->getV(vv);
      printf("v: \n");
      for (int j = 0; j < 3; j++) {
	printf("- %.15g\n", vv[j]);
      }
      p->getX(vx);
      printf("x: \n");
      for (int j = 0; j < 3; j++) {
	printf("- %.15g\n", vx[j]);
      }
    }
    printf("INPUT end ----------------------------------------\n");
#endif
  }
  CAVEDisplayBarrier();
  //texture start

  pobjs->init();

  //texture end
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);

  glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
  //multithead tID
  sphereObj[CAVEUniqueIndex()] = gluNewQuadric();
  clyndObj[CAVEUniqueIndex()] = gluNewQuadric();
  discObj[CAVEUniqueIndex()] = gluNewQuadric();
  theBeam[CAVEUniqueIndex()] = glGenLists(1);
  
  glNewList(theBeam[CAVEUniqueIndex()],GL_COMPILE);
  the_beam();
  glEndList();
  
  bobj = new binary(TARGET_DIST_THRESH/10.);
}

void end(void)
{
  for (int i = 0; i < CAVE_MAX_WALLS; i++) {
    if (sphereObj[i] != NULL) {
      gluDeleteQuadric(sphereObj[i]);
    }
  }
}

void step(void)
{
  double pos[PARTICLE_NUMBER_MAX][3];
  double color[PARTICLE_NUMBER_MAX][4];
  if (cm->runstate == 0) {
    if (CAVEMasterDisplay()) {
      vector<int> curlist = cm->data.getCurrentList();
      vector<int>::iterator p;
      double incl = 0.001;
      vector<PARTICLE_INF>&poslistV = cm->data.getCurrentPosInf();
      poslistV.clear();
      PARTICLE_INF pos_inf = PARTICLE_INF_INIT;
      poslistV.resize(cm->data.getIDNum(),pos_inf);
      if (cm->is_acc && cm->interval + incl < 1.0) {
	cm->interval += incl;
	cm->is_acc = false;
      }
      
      if (cm->is_dec && cm->interval - incl > 0.001) {
	cm->interval -= incl;
	cm->is_dec = false;
      }
      int num=0;

      for (p = curlist.begin(); p != curlist.end(); p++) {
	if(*p<0){
	  continue;
	}
    	Particle *pt = cm->data.getData(*p);
    	pt->extrapolate(cm->t_dat, cm->scale, pos[num]);
    	pos_inf.id = pt->getId();
    	for(int i=0;i<3;i++){
    	  pos_inf.pos.pos[i] = pos[num][i];
    	}
    	pt->getV(&(pos_inf.vel),cm->scale);
	//	poslistV.push_back(pos_inf);
	poslistV[pos_inf.id-1] = pos_inf;

    	num++;
      }
      Motion::GetInstance()->FindBinary(cm->t_dat,cm->scale);

      bobj->color_set(color);
      pobjs->set_x(pos);
      pobjs->set_color(color);
      if(cm->beam_flag){
	cm->SelectParticle();
      }else if(cm->beam_clear_flag){
	cm->allClear();
      }
    }
    CAVEDisplayBarrier();
  }else{
    if(CAVEMasterDisplay()){
      vector<int> curlist = cm->data.getCurrentList();
      vector<int>::iterator p;
      double incl = 0.001;
      vector<PARTICLE_INF>&poslistV = cm->data.getCurrentPosInf();
      poslistV.clear();
      PARTICLE_INF pos_inf = PARTICLE_INF_INIT;
      poslistV.resize(cm->data.getIDNum(),pos_inf);
      if (cm->inc > 0) {
	if (cm->t_sys < cm->t_dat_max) {
	  cm->t_sys += cm->interval;
	} else {
	  cm->t_sys = 0;
	  cm->frame_dat = -1;
	  cm->allClear();
	  Motion::GetInstance()->init();
	}
	
	while (cm->frame_dat < cm->data.getDataNum() - 1) {
	  if (cm->data.getData(cm->frame_dat + 1)->getTime() > cm->t_sys) {
	    break;
	  }
	  cm->frame_dat++;
	  cm->t_dat = cm->data.setCurrentParticle(cm->frame_dat);
	}
      }
      else{
	if (cm->t_sys > 0) {
	  cm->t_sys -= cm->interval;
	} else {
	  cm->t_sys = ((int)(cm->t_dat_max / cm->interval) + 1) * cm->interval;
	  cm->frame_dat = cm->data.getDataNum();
	  cm->allClear();
	  Motion::GetInstance()->init();
	}
	while (cm->frame_dat > 0) {
	  if (cm->data.getData(cm->frame_dat - 1)->getTime() < cm->t_sys) {
	    break;
	  }
	  cm->frame_dat--;
	  cm->t_dat = cm->data.setCurrentParticle(cm->frame_dat);
	}
      }

      int num = 0;
      for (p = curlist.begin(); p != curlist.end(); p++) {
	if(*p<0){
	  continue;
	}
	Particle *pt = cm->data.getData(*p);
	pt->extrapolate(cm->t_dat, cm->scale, pos[num]);
	pos_inf.id = pt->getId();
	for(int i=0;i<3;i++){
	  pos_inf.pos.pos[i] = pos[num][i];
	}
	pt->getV(&(pos_inf.vel),cm->scale);
	//	poslistV.push_back(pos_inf);
	poslistV[pos_inf.id-1] = pos_inf;
	num++;

	if(!cm->target_id.empty()
	   &&pt->getId()==cm->target_id.front()){
	  float color_val = (float)( (pt->getVLen() < cm->vmax ? pt->getVLen() : cm->vmax) - TRAJ_COLOR_BASE );
	  TARGET_POS tpos = { pos_inf.pos.pos[0], pos_inf.pos.pos[1], pos_inf.pos.pos[2], { color_val, color_val, color_val }  };
	  if (cm->traj.front().size() == TRAJ_MAX) {
	    vector<TARGET_POS>::iterator st = cm->traj.front().begin();
	    cm->traj.front().erase(st);
	  }
	  queue< vector<TARGET_POS> >&t_queue = cm->traj;
	  t_queue.front().push_back(tpos); 
	}else if(!cm->target_id.empty()
		 &&pt->getId()==cm->target_id.back()){
	  
	  float color_val = (float)( (pt->getVLen() < cm->vmax ? pt->getVLen() : cm->vmax) - TRAJ_COLOR_BASE );
	  TARGET_POS tpos = { pos_inf.pos.pos[0], pos_inf.pos.pos[1],
			      pos_inf.pos.pos[2], { color_val, color_val, color_val }  };
	  if(!cm->traj.empty()){
	    
	    if (cm->traj.back().size() == TRAJ_MAX) {
	      vector<TARGET_POS>::iterator st = cm->traj.back().begin();
	      cm->traj.back().erase(st);
	    }
	    //>>>>>>> test3_b
	  }
	  queue< vector<TARGET_POS> >&t_queue = cm->traj;
	  t_queue.back().push_back(tpos);
	}
      }
      
      /*		cout << setprecision(15)
			<< "interval: " << cm->interval << " t_sys: " << cm->t_sys
			<< " frame_dat: " << cm->frame_dat << " t_dat: " << cm->t_dat 
			<< " time: " << CAVEGetTime() << endl;
      */
      Motion::GetInstance()->FindBinary(cm->t_dat,cm->scale);
      bobj->color_set(color);
      pobjs->set_x(pos);
      pobjs->set_color(color);

      if(cm->beam_flag){
	cm->SelectParticle();
      }else if(cm->beam_clear_flag){
	cm->allClear();
      }
    }
    CAVEDisplayBarrier();
  }
}

void draw_grid(void)
{
  char buf[4];
  double label_pos = 5.0;
  sprintf(buf, "%.1f", label_pos);
  glPushAttrib(GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT);
  glDisable(GL_LIGHTING);

  // axes
  //x_axes
  glLineWidth(2.0);
  //red
  glColor3d(0.8, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3d(GRID_MIN, 0.0, 0.0);
  glVertex3d(GRID_MAX, 0.0, 0.0);
  glEnd();
  //x_axes end


  if(cm->char_state){
    glRasterPos3d(label_pos, 0.0, 0.0);
    for (int i = 0; i < strlen(buf); i++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buf[i]);
    }
  }

  //y_axes
  //green
  glColor3d(0.0, 0.8, 0.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, GRID_MIN, 0.0);
  glVertex3d(0.0, GRID_MAX, 0.0);
  glEnd();
  //y_axes end
	
  glRasterPos3d(0.0, label_pos, 0.0);
  for (int i = 0; i < strlen(buf); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buf[i]);
  }

  //z_axes
  //blue
  glColor3d(0.0, 0.0, 0.8);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, GRID_MIN);
  glVertex3d(0.0, 0.0, GRID_MAX);
  //z_axes end
  glEnd();

  glRasterPos3d(0.0, 0.0, label_pos);
  for (int i = 0; i < strlen(buf); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buf[i]);
  }

  // grid
  glColor3d(0.5, 0.5, 0.5);
  glLineWidth(1.0);
  for (int i = 1; i <= GRID_NUM; i++) {
    double hpos = GRID_INTERVAL * i;
    glBegin(GL_LINES);
    glVertex3d(GRID_MIN, 0.0, hpos);
    glVertex3d(GRID_MAX, 0.0, hpos);
    glVertex3d(GRID_MIN, 0.0, -hpos);
    glVertex3d(GRID_MAX, 0.0, -hpos);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(hpos, 0.0, GRID_MIN);
    glVertex3d(hpos, 0.0, GRID_MAX);
    glVertex3d(-hpos, 0.0, GRID_MIN);
    glVertex3d(-hpos, 0.0, GRID_MAX);
    glEnd();
  }

  glPopAttrib();
}

void get_angl(float unitVec[],double *angular,double *azimuth){
  *angular = atan2(unitVec[0],unitVec[2]);
  *angular = *angular*180.0/M_PI;
  *azimuth = acos(unitVec[1]);
  *azimuth = *azimuth*180.0/M_PI;
  *azimuth = 90.0-*azimuth;
}

void draw_beam(void)
{

  float wandvec[3];
  float beam[3];
  CAVEGetPosition(CAVE_WAND_NAV, beam);
  CAVEGetVector(CAVE_WAND_FRONT_NAV, wandvec);
  if (!cm->beam_flag) {
    return;
  }
  glPushAttrib(GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT);
  {
    glDisable(GL_LIGHTING);
    glLineWidth(3.0);
    glPushMatrix();
    {
      glEnable(GL_LIGHTING);
      glTranslated(beam[0],beam[1],beam[2]); 
      glPushMatrix();
      {
	double azimuth,angular,dist;
	double beaml=0.0;	    
	glColor3d(1.0,1.0,1.0);
	for(int i=0;i<3;i++){
	  beaml += pow(BEAM_SCALE*wandvec[i],2.0);
	}
	   
	/*	       cout << "main " << 
		       "x " << beam[0] + (BEAM_SCALE*cm->wandvec[0])<<endl
		       << "y " << beam[1] + (BEAM_SCALE*cm->wandvec[1])<<endl
		       <<"z "<<beam[2] + (BEAM_SCALE*cm->wandvec[2])<<endl;
	*/	
	dist = sqrt(dist);
	beaml = sqrt(beaml);
	get_angl(wandvec,&angular,&azimuth);
	glRotated(angular,0.0,1.0,0.0);
	glRotated(-azimuth,1.0,0.0,0.0);
	gluCylinder(clyndObj[CAVEUniqueIndex()],BEAM_WIDTH,BEAM_WIDTH,beaml,16,16);
	gluDisk(discObj[CAVEUniqueIndex()],0.0,BEAM_WIDTH,16,16);
      }
      glPopMatrix();
      glPushMatrix();
      {
	glTranslated(wandvec[0]*(BEAM_SCALE),wandvec[1]*(BEAM_SCALE),wandvec[2]*(BEAM_SCALE));
	      
	glRotatef(cm->rot,0.0,1.0,0.0);
	glCallList(theBeam[CAVEUniqueIndex()]);
      }
      glPopMatrix();
      glDisable(GL_LIGHTING);
    }
    glPopMatrix();
  }
  glPopAttrib();
}



//<<<<<<< HEAD
//=======
void Cross(double *orientV,double *diff_velV,GLdouble *ang_momV){
  ang_momV[0] = (orientV[1]*diff_velV[2] - orientV[2]*diff_velV[1])/2.0;
  ang_momV[1] = (orientV[2]*diff_velV[0] - orientV[0]*diff_velV[2])/2.0;
  ang_momV[2] = (orientV[0]*diff_velV[1] - orientV[1]*diff_velV[0])/2.0; 
}

void get_omega(PARTICLE_POS *pos,PARTICLE_VEL *vel,double dist,GLdouble omega[3]){
  double orientV[3],diff_velV[3];
  GLdouble ang_momV[3];
  for(int i=0;i<3;i++){
    orientV[i] = pos[0].pos[i] - pos[1].pos[i];
    diff_velV[i] = vel[0].vel[i] - vel[1].vel[i];
  }

  Cross(orientV,diff_velV,ang_momV);
  for(int i=0;i<3;i++){
    omega[i] = ang_momV[i]/dist;
  }

}

void draw_arrow(double x,double y,double z,double angular,double azimuth,double length);

void draw_arrow(PARTICLE_POS pos,double angular,double azimuth,double length){
  draw_arrow((double)(pos.pos[0]),(double)(pos.pos[1]),(double)(pos.pos[2]),angular,azimuth,length);
}
void draw_arrow(double x,double y,double z,double angular,double azimuth,double length){


  glPushMatrix();
  {
    glTranslated(x,y,z);
    glRotated(angular,0.0,1.0,0.0);
    glRotated(-azimuth,1.0,0.0,0.0);
    glScaled(1.0/cm->scale,1.0/cm->scale,length/cm->scale);
    glCallList(theArrow[CAVEUniqueIndex()]);
  }
  glPopMatrix();
}



void draw_binary()
{
  double angular,azimuth,length;
  GLdouble omega[3];
  Motion *mo = Motion::GetInstance();
  vector< pair<string,BINARY> >binlist(mo->GetBinaryMap().begin(),mo->GetBinaryMap().end());
  vector< pair<string,BINARY> >::iterator bp;
  BINARY bi_buff;
  glPushMatrix();
  {
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    /*    for(bp=binlist.begin();bp!=binlist.end();bp++){
      bi_buff = (*bp).second;
      glColor4d(1.0,1.0,1.0,(double)(bi_buff.count)/30.0);
      get_omega(bi_buff.pos,bi_buff.vel,bi_buff.dist,omega);
      get_inf_V(omega,&angular,&azimuth,&length);
      draw_arrow(bi_buff.com,angular,azimuth,length);
      }*/
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    
    glRotated(cm->theta, 0.0, 0.0, 1.0);
    glRotated(cm->phi, 1.0, 0.0, 0.0);
    glColor3d( 1.0, 1.0, 1.0 );
    
    glLineWidth(2.0);
    glBegin(GL_LINES);

    for(bp = binlist.begin();bp!=binlist.end();bp++){
      bi_buff = (*bp).second;
      glVertex3d(bi_buff.pos[0].pos[0],bi_buff.pos[0].pos[1],bi_buff.pos[0].pos[2]);

      glVertex3d(bi_buff.pos[1].pos[0],bi_buff.pos[1].pos[1],bi_buff.pos[1].pos[2]);
#ifdef DEBUG
      CAVEDisplayBarrier();
      {
 	if(CAVEMasterDisplay()){
 	  printf("%s(%d)\n",__FILE__,__LINE__);fflush(stdout);
 	}
      }
      CAVEDisplayBarrier();
#endif
    }
    glEnd();
  }
  glPopMatrix();
  CAVEDisplayBarrier();
}

//>>>>>>> test3_b
void display(void)
{
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_COLOR_MATERIAL);
  glPushMatrix();
  {
    CAVENavTransform();
    draw_beam();
    glTranslated(ORIG[0], ORIG[1], ORIG[2]);
    glRotatef(cm->rot,0.0,1.0,0.0); 
    draw_grid();
    //    glEnable(GL_LIGHTING);
    glRotated(cm->theta, 0.0, 0.0, 1.0);
    glRotated(cm->phi, 1.0, 0.0, 0.0);
    GLdouble color[PARTICLE_NUMBER_MAX][4];
    bobj->color_set(color);
    pobjs->set_color(color);
    pobjs->draw();
    //    glDisable(GL_LIGHTING);

    double r = cm->GetRadius();
    Motion *mo = Motion::GetInstance();
    vector<PARTICLE_INF> poslistV = cm->data.getCurrentPosInf();
    vector<PARTICLE_INF>::iterator p;
    
    for(p=poslistV.begin();p!=poslistV.end();p++){
      char idbuf[10];
      //<<<<<<< HEAD
      glPushMatrix();
      {

	sprintf(idbuf, "%d", p->id);
	glEnable(GL_LIGHTING);
	if (!cm->target_id.empty()
	    &&(p->id == cm->target_id.front()
	       ||p->id==cm->target_id.back())) {
		
	  glColor3d( 1.0, 1.0, 1.0 );
	}
	    
	glRotated(cm->theta, 0.0, 0.0, 1.0);
	glRotated(cm->phi, 1.0, 0.0, 0.0);
	glTranslated(p->pos.pos[0],
		     p->pos.pos[1],
		     p->pos.pos[2]);
      }

      glDisable(GL_BLEND);
      glPopMatrix();
      glDisable(GL_LIGHTING);
      glRasterPos3d(p->pos.pos[0] + r,
		    p->pos.pos[1] + r,
		    p->pos.pos[2] + r);
	
      //trajectory


      if(!cm->target_id.empty()
	 &&p->id == cm->target_id.front()){
	if(cm->char_state==1){
	  glColor3f(0.0,0.0,0.0);
	  for (int i = 0; i < strlen(idbuf); i++) {
	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, idbuf[i]);
	  }
	}
	//	if (cm->runstate == 1) {
		
	  // trajectory
	  //				cout << "traj: " << pt->getVLen() << " " << cm->vmax << " " << color_val << endl;

		
	  glLineWidth(1.0);
	  for (int i = cm->traj.front().size() - 1; i > 0; i--) {
	    vector<TARGET_POS> target_list = cm->traj.front();
	    TARGET_POS target = target_list[i];
	    glColor3f(target.color[0],target.color[1],target.color[2]);
	    glBegin(GL_LINES);
	    glVertex3d(cm->traj.front()[i].x,
		       cm->traj.front()[i].y,
		       cm->traj.front()[i].z);
	    glVertex3d(cm->traj.front()[i-1].x,
		       cm->traj.front()[i-1].y, 
		       cm->traj.front()[i-1].z);
	    glEnd();
	  }
		
	  //	}
      }else if(!cm->target_id.empty()
	       &&p->id==cm->target_id.back()){
	    
	if(cm->char_state == 1){
	  glColor3f(0.0,0.0,0.0);
	  for (int i = 0; i < strlen(idbuf); i++) {
	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, idbuf[i]);
	  }
	}

	//	if(cm->runstate == 1){
	  glLineWidth(1.0);
	  for (int i = cm->traj.back().size() - 1; i > 0; i--) {
	    vector<TARGET_POS> target_list = cm->traj.back();
	    TARGET_POS target = target_list[i];
	    glColor3f(target.color[0],target.color[1],target.color[2]);
	    glBegin(GL_LINES);
		    
	    glVertex3d(cm->traj.back()[i].x,
		       cm->traj.back()[i].y,
		       cm->traj.back()[i].z);
	    glVertex3d(cm->traj.back()[i-1].x,
		       cm->traj.back()[i-1].y,
		       cm->traj.back()[i-1].z);
	    glEnd();
		    
	  }
	  //	}
      }else{
	if(cm->char_state){
	  glColor3f(0.0,0.0,1.0);
	  for (int i = 0; i < strlen(idbuf); i++) {
	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, idbuf[i]);
	  }
	}
      }
    }
    
    bobj->draw_arrow();
    bobj->draw_line();
  }

  glPopMatrix();
}

int main(int argc, char *argv[])
{
  string filename;

	
  if (argc == 2) {
    filename = argv[1];
  } else {
    cout << "Enter the name of the input file:" << endl;
    cin >> filename;
  }
  //	cout << "Input file: " << filename << endl;
  ui = UI::GetInstance();
  cm = Common::GetInstance();
  glutInit(&argc, argv);
  CAVEConfigure(&argc, argv, NULL);

  CAVEInitApplication((CAVECALLBACK)init, 1, filename.c_str());
  CAVEDisplay(display, 0);
  CAVEFrameFunction(step, 0);
  CAVEInit();
  float headpos[3];
  CAVEGetPosition(CAVE_HEAD, headpos);
  while (!CAVEgetbutton(CAVE_ESCKEY)) {
    ui->Keyboard();
    ui->Joystick();
    ui->Navigation();

    CAVEUSleep(10);
  }

  end();
  CAVEExit();
}
