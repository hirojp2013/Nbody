#include"color_legend_hue.hpp"

color_legend_hue::color_legend_hue(const double min_,const double max_){
  min = min_;
  max = max_;
  recp_length = 1.0/(max-min);
}

void color_legend_hue::color_map(double x,double a,GLdouble color[4]){
  double tmp[4];
  color_map(x,tmp);
  for(int i=0;i<3;i++){
    color[i] = tmp[i];
  }
  color[3] = a;
}

void color_legend_hue::color_map(double x,GLdouble color[3]){
  float h = (min+x)*recp_length;
  hsv hsvobj;
  //  printf("%s(%d)\n",__FILE__,__LINE__);
  //  printf("%f\n",h);
  //  printf("%f\n",recp_length);
  hsvobj.hsv2rgb(h,1.,1.,color);
}
