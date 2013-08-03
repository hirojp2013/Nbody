#include"color_legend_rgb.hpp"

color_legend_rgb::color_legend_rgb(double min_,double max_,double dx_){
  max =max_;
  min = min_;
  dx = dx_;
  dx_2 = 2*dx;
  cof = 6.-dx_2;
  length =max-min;
  recp_length = 1./length;
  red_r = 5.0;
  red_l = 4.0;
  green_r = 4.0;
  green_l = 2.0;
  blue_r = 2.0;
  blue_l = 1.0;
  red_reg2 = red_r-red_l+2.0;
  green_reg2 = green_r-green_l+2.0;
  blue_reg2 = blue_r-blue_l+2.0;
}

void color_legend_rgb::color_map(double x,double a,double color[4]){
  double tmp[4];
  color_map(x,tmp);
  for(int i=0;i<3;i++){
    color[i] = tmp[i];
  }
  color[3] = a;
}
void color_legend_rgb::color_map(double x,double color[3]){

  double g = solve_g(x);
  color[0]=trape_red(g);
  color[1]=trape_green(g);
  color[2]=trape_blue(g);
}

double color_legend_rgb::solve_g(double x){
  double f = recp_length*(x-min);
  return cof*f+dx;
}

double color_legend_rgb::trape_red(double g){
  trapezoid(g,red_reg2,red_l,red_r);
}

double color_legend_rgb::trape_green(double g){
  trapezoid(g,green_reg2,green_l,green_r);
}
double color_legend_rgb::trape_blue(double g){
  trapezoid(g,blue_reg2,blue_l,blue_r);
}

double color_legend_rgb::trapezoid(double g,double region2,double left,double right){
  return 0.5*(region2-(fabs(g-left)+fabs(g-right)));
}
