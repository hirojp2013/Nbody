//
// vfive: Vector Field Interactive Visualization Environment
//
// line_advector_point.cpp: line advector, the moving point.
//
//                by Akira Kageyama  (kage@jamstec.jo.jp)  2008.05.20
//
// copied from tracer_line.cpp
//
// Change line_advector_point -> tube_advector_point
//                by Kaori Murata 2010.01
//  
// Please read the file "LICENCE_ja.txt"(in Japanese) or "LICENCE_en.txt" (in English)
// before you use this software. 

#include "vfive.h"


extern vfive::Vfive* v5;

namespace vfive
{

static const ffloat_ DT_FACTOR = 0.1;

TubeAdvector_point:: TubeAdvector_point(Data* d) : data(d)
{
//  radius = 0.1;
  calcToggle = 0;

  for(int i=0;i<3;i++){
    pos[i] = 0.0;
  }

  for(int i=0;i<4;i++){
    color[i] = 0.0;
  }

  on = 0;
  h = 0.0;
  setRkConsts();
  svec = 0;
}


void 
TubeAdvector_point:: setRkConsts()
{
  c01 = h/9.0;
  c02 = h*0.4166666666666667e-1;
  c03 = h*0.125;
  c04 = h/6.0;
  c05 = h*0.5;
  c06 = h*0.6666666666666667;
  c07 = h/3.0;
  c08 = h*0.3750;
  c09 = h*0.1333333333333333e1;
  c10 = h*0.3333333333333333e1;
  c11 = h*0.7e1;
  c12 = h*0.9666666666666667e1;
  c13 = h*0.1533333333333333e2;
  c14 = h*0.6111111111111111;
  c15 = h*0.1166666666666667e1;
  c16 = h*0.1375e1;
  c17 = h*0.8333333333333333;
  c18 = h*0.4390243902439024;
  c19 = h*0.8780487804878049;
  c20 = h*0.1304878048780488e1;
  c21 = h*0.2097560975609756e1;
  c22 = h*0.2963414634146341e1;
  c23 = h*0.4317073170731707e1;
  c24 = h*0.3214285714285714e-1;
  c25 = h*0.4880952380952381e-1;
  c26 = h*0.2571428571428571;
  c27 = h*0.3238095238095238;
}


int
TubeAdvector_point:: genRkh(Data* data,
			    ffloat_ *tim, ffloat_ y[], int n, ffloat_ f[],
		     int nsteps, 
		     int (*func)(Data*, ffloat_, ffloat_ *, ffloat_ *,int)) 
{
       /* general purpose Runge-Kutta-Huta formula */
       /*              Kageyama, Akira  <97.09.10> */
       /*******  runge-kutta-huta formulas  ( sixth order 8-stage ) **********
           tim          real*8       time
           y(n)         real*8       input and output
           n            integer*4    dimension of the differential equation
           h            real*8       step size
           f(n,nl)      real*8       work aray for calculation ( nl >= 9 )

           <<< reference >>>
                " improved sixth-order runge-kutta formulas and approximate
                continuous solution of ordinary differential equation "
        **********************************************************************/

        int     i, iout;
        ffloat_  x = *tim;

        for ( i=0;i<n;i++ ) {
            f[i] = y[i];
	}

        while (nsteps--) {

            /* 1st stage */
            if ( iout = (*func)(data,x,f,f+2*n,svec) ) return(iout);
            for ( i=0; i<n; i++ ) {
                f[n+i] = c01*f[2*n+i]+f[i];
	    }

            /* 2nd stage */
            if ( iout = (*func)(data,x+c01,f+n,f+3*n,svec) ) return(iout);
            for ( i=0; i<n; i++) {
                f[n+i] = c02*f[2*n+i]+c03*f[3*n+i]+f[i];
	    }

            /* 3rd stage */
            if ( iout = (*func)(data,x+c04,f+n,f+4*n,svec) ) return(iout);
            for ( i=0; i<n; i++) {
                f[n+i] = c04*f[2*n+i]-c05*f[3*n+i]+c06*f[4*n+i]+f[i];
	    }

            /* 4th stage */
            if ( iout = (*func)(data,x+c07,f+n,f+5*n,svec) ) return(iout);
            for ( i=0; i<n; i++) {
                f[n+i] = c03*f[2*n+i]+c08*f[5*n+i]+f[i];
	    }

            /* 5th stage */
            if ( iout = (*func)(data,x+c05,f+n,f+6*n,svec) ) return(iout);
            for ( i=0; i<n; i++) {
                f[n+i] = -c09*f[2*n+i]+c10*f[6*n+i]
                         -c11*f[3*n+i]-c12*f[5*n+i]
                         +c13*f[4*n+i]+    f[i];
	    }

            /* 6th stage */
            if ( iout = (*func)(data,x+c06,f+n,f+7*n,svec) ) return(iout);
            for ( i=0; i<n; i++) {
                f[n+i] = -c01*f[2*n+i]+c03*f[7*n+i]
                         +c14*f[6*n+i]-c15*f[4*n+i]
                         +c16*f[3*n+i]+    f[i];
	    }

            /* 7th stage */
            if ( iout = (*func)(data,x+c17,f+n,f+8*n,svec) ) return(iout);
            for ( i=0; i<n; i++) {
                 f[n+i] = -c18*f[7*n+i]+c19*f[8*n+i]
                          +c20*f[2*n+i]-c21*f[6*n+i]
                          -c22*f[3*n+i]+c23*f[5*n+i]+f[i];
	    }

            /* 8th stage */
            if ( iout = (*func)(data,x+h,f+n,f+3*n,svec) ) return(iout);
            for ( i=0; i<n; i++) {
                 y[i] = f[i] = (f[5*n+i]+f[7*n+i])*c24
                              +(f[2*n+i]+f[3*n+i])*c25
                              +(f[4*n+i]+f[8*n+i])*c26
                               +f[6*n+i]*c27+f[i];
	    }

            x += h;
	}

        *tim = x;

        return(0);
}



void
TubeAdvector_point::start(float* p, int sv, int para, float* col) 
{
//  radius = 0.1;

  vec_f2ff(3, pos, p);
  vec_f2f(4, color, col);

  on = 1;

  ffloat_ max_v = v5->data->vector_fld[sv]->vmax;
  ffloat_ dh;

  dh = (v5->data->grid_size_min / max_v ) * DT_FACTOR;

  h = para*dh;
  setRkConsts();
  svec = sv;
  calcToggle = 1;
}



void
TubeAdvector_point::integrate()
{
  ffloat_ tim;
  ffloat_ fwork[30];
  int iout;

  iout = genRkh(data,
		&tim, 
		pos, 
		3,               // 3 component vector
		fwork,           // work region
		5,               // Integrate 5 steps
//		intpol_get_vect_for_tubeAdvector);  // function to get vector
		intpol_get_vect_for_tracer);  // function to get vector

  // When the orbit is OK, iout=0, otherwise 1 

  if (iout==0) {
    calcToggle = 1;                  // Continue the integration.
  }
  else {
    calcToggle = 0;
  }
}

}
