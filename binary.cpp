#include "binary.h"
#include "angular_vel.h"
#include "common.h"

const double MIN = 0;
const double MAX = 1.;
binary::binary(const double length):clh(MIN,MAX),LENGTH(length){
  ang_vel = new angular_vel;
  cm = Common::GetInstance();
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
    printf("state NEARBY\n");
    glEnable(GL_BLEND);
    clh.color_map(p_inf.kin,nearby_alpha_boundary(p_inf),color);
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    //    printf("%f %f %f %f\n",color[0],color[1],color[2],color[3]);
    break;
  case AROUND:
    printf("state AROUND\n");
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    //    printf("%d\n",p_inf.id);
    glEnable(GL_BLEND);
    clh.color_map(p_inf.kin,around_alpha_boundary(p_inf),color);
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    //    printf("%f %f %f %f\n",color[0],color[1],color[2],color[3]);
    break;
  case ENG_SUM:
    printf("state ENG_SUM\n");
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
    //    printf("%s(%d)\n",__FILE__,__LINE__);

    return 0.0;
  }
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",RECIP_LENGTH);
  printf("id %d\n",par_inf.id);
  printf("kin %f\n",par_inf.kin);
  printf("pot %f\n",par_inf.pot);

  par_inf.pot = par_inf.pot*LENGTH*5;
  return ( isinf(par_inf.pot) ? 1.0: par_inf.pot); 

}

double binary::eng_sum_alpha_boundary(PARTICLE_INF par_inf){
  if(par_inf.l == NOT_MAKE_BINARY){
    return 0.0;
  }
  printf("id %d\n",par_inf.id);
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  printf("length %f\n",par_inf.l);
  return 1.0;
}

double binary::eng_sum_color_boundary(PARTICLE_INF par_inf){
  if(par_inf.eng_sum > 0){
    return 0.0;
  }
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  printf("id %d\n",par_inf.id);
  printf("eng_sum %f\n",par_inf.eng_sum);
  return fabs(par_inf.eng_sum*LENGTH);
}

double binary::nearby_alpha_boundary(PARTICLE_INF par_inf){
  if(par_inf.l == NOT_MAKE_BINARY){
    //    printf("%s(%d)\n",__FILE__,__LINE__);

    return 0.0;
  }
  double pot = (1.0/par_inf.l)*LENGTH;
  printf("id %d\n",par_inf.id);
  printf("kin %f\n",par_inf.kin);
  printf("length %f\n",par_inf.l);

  return ( isinf(pot) ? 1.0: pot); 
}
