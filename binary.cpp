#include "binary.h"
const double MIN = 0;
const double MAX = 1.;
binary::binary(const double length):clh(MIN,MAX),RECIP_LENGTH(1./length){
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
    clh.color_map(p_inf.kin,pot_alph_value_bounday(p_inf.l),color);
    //    printf("%s(%d)\n",__FILE__,__LINE__);
    //    printf("%f %f %f %f\n",color[0],color[1],color[2],color[3]);
    break;
    //  case AROUND:break;
  default:
    color[0] = 0.0;
    color[1] = 0.0;
    color[2] = 1.0;
    color[3] = 1.0;
    break;
  }
}

double binary::pot_alph_value_bounday(double length){
  if(length == NOT_MAKE_BINARY){
    //    printf("%s(%d)\n",__FILE__,__LINE__);

    return 0.0;
  }
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",length);
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",RECIP_LENGTH);

  double pot = (1.0/length)/RECIP_LENGTH;
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",pot);

  return ( isinf(pot) ? 1.0: pot); 
}
