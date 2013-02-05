#include "binary.h"
#include "angular_vel.h"
#include "common.h"
#include "motion.h"

const double MIN = 0;
const double MAX = 1.;
binary::binary(const double length):clh(MIN,MAX),LENGTH(length){
  ang_vel = new angular_vel;
  cm = Common::GetInstance();
}

void binary::draw_line(){
  GLdouble omega[3];
  Motion *mo = Motion::GetInstance();
  vector< pair<string,BINARY> >binlist(mo->GetBinaryMap().begin(),
				       mo->GetBinaryMap().end());
  vector< pair<string,BINARY> >::iterator bp;
  BINARY bi_buff;
  if(cm->binary_state == LINE){
    glPushMatrix();
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
    glPopMatrix();
  }
}

void binary::draw_arrow(){
  if(cm->binary_state == ARROW){
    printf("state ARROW\n");
    ang_vel->draw_arrow();
  }
}

void binary::color_set(PARTICLE_INF p_inf,
		       GLdouble color[4]){
  switch(cm->binary_state){
  case NEARBY:
    glEnable(GL_BLEND);
    clh.color_map(p_inf.kin,nearby_alpha_boundary(p_inf),color);
    break;
  case AROUND:
    glEnable(GL_BLEND);
    clh.color_map(p_inf.kin,around_alpha_boundary(p_inf),color);
    break;
  case ENG_SUM:
    glEnable(GL_BLEND);
    clh.color_map(eng_sum_color_boundary(p_inf),
		  eng_sum_alpha_boundary(p_inf),
		  color);
    break;
  default:
    color[0] = 0.0;
    color[1] = 0.0;
    color[2] = 1.0;
    color[3] = 1.0;
    break;
  }
}

double binary::around_alpha_boundary(PARTICLE_INF par_inf){
  if(par_inf.l == NOT_MAKE_BINARY){
    return 0.0;
  }
  par_inf.pot = par_inf.pot*LENGTH*5;
  return ( isinf(par_inf.pot) ? 1.0: par_inf.pot); 
}

double binary::eng_sum_alpha_boundary(PARTICLE_INF par_inf){
  if(par_inf.l == NOT_MAKE_BINARY){
    return 0.0;
  }
  return 1.0;
}

double binary::eng_sum_color_boundary(PARTICLE_INF par_inf){
  if(par_inf.eng_sum > 0){
    return 0.0;
  }
  return fabs(par_inf.eng_sum*LENGTH);
}

double binary::nearby_alpha_boundary(PARTICLE_INF par_inf){
  if(par_inf.l == NOT_MAKE_BINARY){
    return 0.0;
  }
  double pot = (1.0/par_inf.l)*LENGTH;
  return ( isinf(pot) ? 1.0: pot); 
}
