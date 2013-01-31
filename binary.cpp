#include "binary.h"
#include "angular_vel.h"
#include "common.h"

const double MIN = 0;
const double MAX = 1.;
binary::binary(const double length):clh(MIN,MAX),LENGTH(length){
  ang_vel = new angular_vel;
  cm = Common::GetInstance();
}

void binary::draw(){
  ang_vel->draw_arrow();
}

void binary::color_set(PARTICLE_INF p_inf,
		       GLdouble color[4]){
  switch(cm->binary_state){
  case NEARBY:
    glEnable(GL_BLEND);
    clh.color_map(p_inf.kin,pot_alpha_value_boundary(p_inf.l),color);
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    //    printf("%f %f %f %f\n",color[0],color[1],color[2],color[3]);
    break;
    //  case AROUND:break;
  case ENG_SUM:
    glEnable(GL_BLEND);
    clh.color_map(eng_sum_color_boundary(p_inf.eng_sum),
		  eng_sum_alpha_boundary(p_inf.l),
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

double binary::eng_sum_alpha_boundary(double length){
  if(length == NOT_MAKE_BINARY){
    return 0.0;
  }
  printf("%s(%d)\n",__FILE__,__LINE__);
  printf("%f\n",length);
  return 1.0;
}

double binary::eng_sum_color_boundary(double eng_sum){
  if(eng_sum > 0){
    return 0.0;
  }
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",eng_sum);
  return fabs(eng_sum*LENGTH);
}

double binary::pot_alpha_value_boundary(double length){
  if(length == NOT_MAKE_BINARY){
    //    printf("%s(%d)\n",__FILE__,__LINE__);

    return 0.0;
  }
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",length);
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",RECIP_LENGTH);

  double pot = (1.0/length)*LENGTH;
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",pot);

  return ( isinf(pot) ? 1.0: pot); 
}
