//
// vfive: Vector Field Interactive Visualization Environment
//
// line_advector.cpp
//
//    - copied from tracer.cpp
//
//                by Akira Kageyama, on 2008.05.20
// Change line_advector to tube_advector
//                by Kaori Murata, on 2010.01.14
//  
// Please read the file "LICENCE_ja.txt"(in Japanese) or "LICENCE_en.txt" (in English)
// before you use this software. 


#include "vfive.h"

extern vfive::Vfive*  v5;

namespace vfive
{


static
tubeAdvector_point_ptr*
create_array_of_tubeAdvector_point_ptr(int ll)
{
    tubeAdvector_point_ptr *a;

    a = (tubeAdvector_point_ptr *)malloc(ll * sizeof(tubeAdvector_point_ptr));
    if (!a) v5_error("create_array_of_tubeAdvector_point_ptr: 1");

    return(a);

}


TubeAdvector::TubeAdvector(Data* d) : data(d)
{
  int i;
  turn_off();
  integration_off();
  svec_ = 0;

  alin = 0;
  show_off();

  point = create_array_of_tubeAdvector_point_ptr(TUBE_ADVECTOR_POINT_MAX);

    for (int j=0; j<TUBE_ADVECTOR_POINT_MAX; j++) {
      point[j] = new TubeAdvector_point(data);
       if(point[j] == NULL) v5_error("can't allocate tubeAdvector_point.");
    }

  strings = NULL;
  

  beam = new PointerBeam(0.3, 1.0, 1.0, 3.0);
  if(beam == NULL) v5_error("can't allocate beam in tube_advector.");

  Color wrk;
  i = 0;
  while (i < data->nvec) {
    vec_f2f(4, coltable[i++], wrk.mizuiro(0.0));
    if (i>=MAX_NVEC) break;
    vec_f2f(4, coltable[i++], wrk.aka(0.6));     // pink.
    if (i>=MAX_NVEC) break;
    vec_f2f(4, coltable[i++], wrk.midori(0.5));  // light green.
    if (i>=MAX_NVEC) break;
    vec_f2f(4, coltable[i++], wrk.murasaki(0.3));  
    if (i>=MAX_NVEC) break;
  }

}


static void
next_point(int& point)
{
     point = (++point) % TUBE_ADVECTOR_POINT_MAX;
    
}



void
TubeAdvector::put_interpolate_points_in_strings()
{
  float x0, y0, z0, x1, y1, z1, distance_sq;
  float pos[3];
  int   i0, i1;
  string_linked_list_element *left_ptr;
  string_linked_list_element *right_ptr;
  // const float CRITICAL_DISTANCE = 0.3;  // feet
  const float CRITICAL_DISTANCE = data->grid_size_min*2; 
  const float CD_SQ = CRITICAL_DISTANCE*CRITICAL_DISTANCE;

  if(strings == NULL) return;
  left_ptr  = strings->first_ptr;
  if ( left_ptr == NULL ) return;

  right_ptr = left_ptr->next_ptr;
  while ( right_ptr != NULL ) {
      if(!is_integration_on()) return;//2010.01.29

    i0 =  left_ptr->particle_index;
    i1 = right_ptr->particle_index;
    if (point[i0]->on == 0 || point[i1]->on == 0 ) continue;
    x0 = point[i0]->pos[0];
    y0 = point[i0]->pos[1];
    z0 = point[i0]->pos[2];
    x1 = point[i1]->pos[0];
    y1 = point[i1]->pos[1];
    z1 = point[i1]->pos[2];
    distance_sq = (x0-x1)*(x0-x1)+(y0-y1)*(y0-y1)+(z0-z1)*(z0-z1);
    if ( distance_sq > CD_SQ ) {
	pos[0] = (x0+x1)/2;    // middle point
	pos[1] = (y0+y1)/2;   
	pos[2] = (z0+z1)/2;   
	point[alin]->erase();                  // delete the old point.
	point[alin]->start(pos, svec(), +1, coltable[svec()]); // positive trace
	strings->insert_list(left_ptr, alin);
	// When point is MAX
	if((alin+1)>=TUBE_ADVECTOR_POINT_MAX){
	    integration_off();
	}
	next_point(alin);
    }

	left_ptr = right_ptr;
	right_ptr = left_ptr->next_ptr;
    
  }
  
}

void
TubeAdvector::release()
{
//changed by Murata 2010.02.08
  static int i_prev=0;
  int sv = svec();
  

  const float RELEASE_INTERVAL_DISTANCE = data->grid_size_min;
  float dis[3];

    dis[0] = beam->tip[0]-(point[i_prev]->pos[0]);
    dis[1] = beam->tip[1]-(point[i_prev]->pos[1]);
    dis[2] = beam->tip[2]-(point[i_prev]->pos[2]);
  if ( vec_norm(dis)> RELEASE_INTERVAL_DISTANCE ) {
    point[alin]->erase();                  // delete the old point.
    point[alin]->start(beam->tip, sv, +1, coltable[sv]); // positive trace
    strings->add_list(alin);
    i_prev=alin;
    next_point(alin);

  }
/*

 static float t_prev = 0.0;  // time when the last point was released.
   int sv = svec();
  
  float t = CAVEGetTime();    // Used for animation


  const float RELEASE_INTERVAL_SECOND = 0.01;  // in second.
  if ( t - t_prev > RELEASE_INTERVAL_SECOND ) {
    point[alin]->erase();                  // delete the old point.
    point[alin]->start(beam->tip, sv, +1, coltable[sv]); // positive trace
    strings->add_list(alin);
    next_point(alin);
    t_prev = t;
  }

*/
}

void
TubeAdvector::integrate()
{

  if ( !is_integration_on() ) return;

 
  //  if ( v5->target->viz() != TUBE_ADVECTOR ) integration_off(); 2010.01.25

  for (int i=0; i<TUBE_ADVECTOR_POINT_MAX; i++) {
    if (point[i]->calc_state()) point[i]->integrate();
  }
}

void
TubeAdvector::reset()
{

 CAVESetWriteLock(v5->advect_lock);

  alin = 0;
  string_linked_list_element *current_ptr, *next_ptr;
  for (int i = 0; i < TUBE_ADVECTOR_POINT_MAX; i++) 
    point[i]->erase();

   if(strings != NULL){// 2008.11.20
    current_ptr = strings->first_ptr;
    while (current_ptr != NULL) {
      next_ptr = current_ptr->next_ptr;
      delete current_ptr;
      current_ptr = next_ptr;
    }
    delete strings;
    strings = NULL;
   }
 CAVEUnsetWriteLock(v5->advect_lock);
}



//added 2010.01.29 by Kaori Murata
//average cross section version
void 
TubeAdvector:: makeCylinder(int isfirst,int ip,float *t){
    float p[3];
    static float p_pre[NKAKU][3], q_pre[NKAKU][3];// vertex point of tube and
    float p_now[NKAKU][3], q_now[NKAKU][3];      // normal vec on vertex
    float u[3];   // 1st normal
    static float v[3];   // 2nd normal
    float w[3];   // work vector
    float nrm, theta, d_theta;
    d_theta = TWOPI / (float)(NKAKU);
    for(int i=0;i<3;i++){
        p[i]= point[ip]->pos[i];
	}
    
    if(isfirst==1){//when first call this function
	w[0] = 1.0;    // Exploring a normal vector to the curve.
	w[1] = 0.0;    // This is just a first trial of work vector.
	w[2] = 0.0;

	nrm = vec_cross_normalf(w,t,u);
	if(nrm < 1.e-5 ) { // On accident, the first trial was parallel
   	    w[0] = 0.0;      // to the curve itself. Retry.
            w[1] = 1.0;
   	    w[2] = 0.0;
	    vec_cross_normalf(w,t,u);
        }
	// Now we got the 1st normal
	vec_cross_normalf(t,u,v);      // constructing the 2nd normal
	for(int j=0; j<NKAKU; j++) {
            theta = d_theta*j;
            q_pre[j][0] = cos(theta)*u[0] + sin(theta)*v[0];
            q_pre[j][1] = cos(theta)*u[1] + sin(theta)*v[1];
            q_pre[j][2] = cos(theta)*u[2] + sin(theta)*v[2];

//            p_pre[j][0] = p[0] + point[ip]->radius*q_pre[j][0];
//            p_pre[j][1] = p[1] + point[ip]->radius*q_pre[j][1];
//	    p_pre[j][2] = p[2] + point[ip]->radius*q_pre[j][2];

            p_pre[j][0] = p[0] + TUBE_RADIUS*q_pre[j][0];
            p_pre[j][1] = p[1] + TUBE_RADIUS*q_pre[j][1];
	    p_pre[j][2] = p[2] + TUBE_RADIUS*q_pre[j][2];
        }
	return;
    }
//	printf("v1 %f,%f,%f\n",v[0],v[1],v[2]);

    w[0] = v[0];    // Exploring a normal vector to the curve.
    w[1] = v[1];    // This is just a first trial of work vector.
    w[2] = v[2];

   nrm = vec_cross_normalf(w,t,u);

   if(nrm < 1.e-5 ) { // On accident, the first trial was parallel
     w[0] = 0.0;      // to the curve itself. Retry.
     w[1] = 1.0;
     w[2] = 0.0;
     vec_cross_normalf(w,t,u);
   }

   // Now we got the 1st normal
   vec_cross_normalf(t,u,v);      // constructing the 2nd normal
   for (int j=0; j<NKAKU; j++) {  
      theta = d_theta*j;
      q_now[j][0] = cos(theta)*u[0] + sin(theta)*v[0];
      q_now[j][1] = cos(theta)*u[1] + sin(theta)*v[1];
      q_now[j][2] = cos(theta)*u[2] + sin(theta)*v[2];
      p_now[j][0] = p[0] + TUBE_RADIUS*q_now[j][0];
      p_now[j][1] = p[1] + TUBE_RADIUS*q_now[j][1];
      p_now[j][2] = p[2] + TUBE_RADIUS*q_now[j][2];

//      p_now[j][0] = p[0] + point[ip]->radius*q_now[j][0];
//      p_now[j][1] = p[1] + point[ip]->radius*q_now[j][1];
//      p_now[j][2] = p[2] + point[ip]->radius*q_now[j][2];
      }
	
   glBegin(GL_TRIANGLE_STRIP);
     for (int j=0; j<NKAKU; j++) {
         glNormal3fv(q_pre[j]);
         glVertex3fv(p_pre[j]);
         glNormal3fv(q_now[j]);
	 glVertex3fv(p_now[j]);
	}
     glNormal3fv(q_pre[0]);
     glVertex3fv(p_pre[0]);
     glNormal3fv(q_now[0]);
     glVertex3fv(p_now[0]);
   glEnd();

   for(int j=0; j<NKAKU; j++) {
      for(int i=0;i<3;i++){
         q_pre[j][i] = q_now[j][i];
         p_pre[j][i] = p_now[j][i];
      }
   }
}

//added 2010.01.29 by Kaori Murata
void
TubeAdvector::draw_Tube()
{

  string_linked_list_element *current_ptr;
  int m,i,p;
  float t[3];
  int f=1;
  
  if(strings == NULL || show == 0) return; //integration->show 2010.01.25
   CAVESetReadLock(v5->advect_lock); 
  
  glPushMatrix();
    current_ptr = strings->first_ptr;
    while(current_ptr!=NULL){
	if(f!=0) m=i=current_ptr->particle_index;
	if(current_ptr->next_ptr==NULL) {
	    if(f!=0){
		CAVEUnsetReadLock(v5->advect_lock); 
		return;
	    }
	    p=i;
	}else{
	    p=current_ptr->next_ptr->particle_index;
	    if(point[p]->on == 0){
	        current_ptr=current_ptr->next_ptr;
	        continue;
	    }
	}
	t[0]=point[p]->pos[0]-point[m]->pos[0];
	t[1]=point[p]->pos[1]-point[m]->pos[1];
	t[2]=point[p]->pos[2]-point[m]->pos[2];
	if(vec_norm(t)==0){
	    t[0]=point[p]->pos[0]-point[i]->pos[0];
	    t[1]=point[p]->pos[1]-point[i]->pos[1];
	    t[2]=point[p]->pos[2]-point[i]->pos[2];
	    if(vec_norm(t)==0){
		current_ptr=current_ptr->next_ptr;
		continue;
	    }
	}
	GLfloat mat0[4];
	GLfloat mat1[4];
	for(int j=0;j<4;j++){
	    mat0[j]=point[i]->color[j]*4.0/5.0;
	    mat1[j]=point[i]->color[j]-mat0[j];
	}
     
	glMaterialfv(GL_FRONT, GL_DIFFUSE,mat0);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat1);
	makeCylinder(f,i,t);
	m=i;
	i=p;
	f=0;
	current_ptr=current_ptr->next_ptr;
    }

  glPopMatrix();
   CAVEUnsetReadLock(v5->advect_lock);      
}



void
TubeAdvector::initialize() 
{

}


void
TubeAdvector::draw()
{
  //  We usually do not show any objects when 
  //  the visualization method is in the 'off' state.
  //  in this tube_advector, however, we want the
  //  wand beam always appear. 2008.04.21. A.K.

  if ( v5->target->viz() == TUBE_ADVECTOR && beam->is_on() ) {
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING); 
    beam->draw();
    glPopAttrib();
  }

  if (on) {
    glPushAttrib(GL_LIGHTING_BIT);
    glEnable(GL_LIGHTING);
     draw_Tube();
    glPopAttrib();
  }
}

void
TubeAdvector::button_being_pressed()
{
  if(!on) return;     //2008.4.21 by N.O.
  if (strings == NULL) return;
  integration_off();
  show_on();

  release();          // Repeated release of new particles.
}

void
TubeAdvector::button_has_pressed()
{
  if(!on) return;     //2008.11.19 by N.O.

  integration_off();
  show_off();
  reset();
  // beam->turn(1);   // it's already on after this viz is selected.

  strings = new String;
}

void
TubeAdvector::button3_has_pressed()
{

  integration_off();
  show_off();
  reset();


  // for debug s
  //  for (int sid=0; sid<current_string_id; sid++) {
  //    printf("============= %d =============\n", sid);
  //     strings[svec()][sid]->print_list();
  //  }
  // for debug e

}


void
TubeAdvector::button_has_released()
{
  if(!on) return;     //2008.11.19 by N.O.
  if (strings == NULL) return; // 2008.11.19
  release(); 
  integration_on();
  show_on();
}

void
String::add_list(int index) {
  string_linked_list_element *new_ptr;

  new_ptr = new string_linked_list_element;
  (*new_ptr).particle_index = index;
  (*new_ptr).next_ptr = first_ptr;
  first_ptr = new_ptr;
};


void
String::insert_list(string_linked_list_element *ptr0, int index)
{
  string_linked_list_element *new_ptr;

  string_linked_list_element *ptr1;

  ptr1 = ptr0->next_ptr;

  //        first_ptr => (next) 
  //                  => (next)
  //                   ....
  //                  => ptr0
  //                  => new_ptr          <---  Insert here.
  //                  => ptr1
  //                  => (next)
  //                   ....

  new_ptr = new string_linked_list_element;
  ptr0->next_ptr = new_ptr;
  new_ptr->particle_index = index;
  new_ptr->next_ptr = ptr1;
  
}



void
String::print_list() {
  string_linked_list_element *current_ptr;

  current_ptr = first_ptr;
  
  while (current_ptr != NULL) {
    printf("  index = %d\n", current_ptr->particle_index);
    current_ptr = current_ptr->next_ptr;
  }
};


}
