#include"angular_vel.h"

angular_vel::angular_vel(){
  aw = new arrow[CAVE_MAX_WALLS];
  cm = Common::GetInstance();
}

void angular_vel::draw_arrow()
{
  double angular,azimuth,length;
  GLdouble omega[3];
  Motion *mo = Motion::GetInstance();
  vector< pair<string,BINARY> >binlist(mo->GetBinaryMap().begin(),
				       mo->GetBinaryMap().end());
  vector< pair<string,BINARY> >::iterator bp;
  BINARY bi_buff;
  glPushMatrix();
  {
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    for(bp=binlist.begin();bp!=binlist.end();bp++){
      bi_buff = (*bp).second;
      glColor4d(1.0,1.0,1.0,(double)(bi_buff.count)/30.0);
      get_omega(bi_buff.pos,bi_buff.vel,bi_buff.dist,omega);
      get_inf_V(omega,&angular,&azimuth,&length);
      //  call_arrow(bi_buff.com,angular,azimuth,length);
      aw[CAVEUniqueIndex()].draw(bi_buff.com,angular,azimuth,length);
    }
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
    }
    glEnd();
  }
  glPopMatrix();
  CAVEDisplayBarrier();
}


void angular_vel::Cross(double *orientV,double *diff_velV,GLdouble *ang_momV){
  ang_momV[0] = (orientV[1]*diff_velV[2] - orientV[2]*diff_velV[1])/2.0;
  ang_momV[1] = (orientV[2]*diff_velV[0] - orientV[0]*diff_velV[2])/2.0;
  ang_momV[2] = (orientV[0]*diff_velV[1] - orientV[1]*diff_velV[0])/2.0; 
}

void angular_vel::get_inf_V(double Vec[],double *angular,double *azimuth,double *length){
  double buf=0.0;
  for(int i=0;i<3;i++){
    buf += pow(Vec[i],2.0);
  }
  *length = sqrt(buf);
  *angular = atan2(Vec[0],Vec[2]);
  *angular = *angular*180.0/M_PI;
  *azimuth = acos(Vec[1]/(*length));
  *azimuth = *azimuth*180.0/M_PI;
  *azimuth = 90.0-*azimuth;
}


void angular_vel::get_omega(PARTICLE_POS *pos,PARTICLE_VEL *vel,double dist,GLdouble omega[3]){
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
