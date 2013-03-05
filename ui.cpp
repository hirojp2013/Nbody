#include "ui.h"

void UI::Navigation(void)
{
  float wand_vec[3];
  float jx = CAVE_JOYSTICK_X;
  float jy = CAVE_JOYSTICK_Y;
  Common *cm = Common::GetInstance();
  if (fabs(jx) > 0.2) {
    cm->rot += jx*ROT_SPEED;
    //		cout << "Navigation jx=" << jx << " dt=" << dt << " angle=" << (jx * 90.0 * dt) << endl;
  }

  if (fabs(jy) > 0.2) {
		
    CAVEGetVector(CAVE_WAND_FRONT, wand_vec);
    //		cout << "Navigation jy=" << jy << " dt=" << dt << " "
    //			<< (wand_pos[0] * v) << " "
    //			<< (wand_pos[1] * v) << " "
    //			<< (wand_pos[2] * v) << endl;

    CAVENavTranslate(SPEED * wand_vec[0] * jy,
		     SPEED * wand_vec[1] * jy,
		     SPEED * wand_vec[2] * jy);
  }
}

void UI::showstep(int direction)
{
  Common *cm = Common::GetInstance();
  cm->runstate = 0;
  int inc_prev = cm->inc;
  if (cm->inc < 0)
    cm->inc = -cm->inc;
  if (cm->inc == 0)
    cm->inc = 1;
  if (direction < 0)
    cm->inc = -cm->inc;
  cout << "Step direction: " << direction << "  inc: " << inc_prev << " -> " << cm->inc << endl;
  //	step();
}

// void UI::show_help(void)
// {
// 	cout << "Keyboard commands\n"
// 		 << "  H, h: stop animation and show this help\n"
// 		 << "  A, a: speed up\n"
// 		 << "  D, d: speed down\n"
// 		 << "  S, s: scale up(S) or down\n"
// 		 << "  R, r: increase(R) the size of points or decrease\n"
// 		 << "  X, x: rotate in some direction\n"
// 		 << "  Y, y: rotate in some other direction\n"
// 		 << "  U, u: move in some direction\n"
// 		 << "  N, n: move in some other direction\n"
// 		 << "  T, t: speed up or down the movement by U/N"
// 		 << endl;
// }

void UI::Keyboard(void)
{
  Common *cm = Common::GetInstance();

  bool is_acc_prev = cm->is_acc;
  bool is_dec_prev = cm->is_dec;
  GLdouble scale_prev = cm->scale;
  GLdouble radius_prev = cm->radius;
  GLdouble phi_prev = cm->phi;
  GLdouble theta_prev = cm->theta;
  //  GLdouble dx_prev = cm->dx;
  //  GLdouble dy_prev = cm->dy;
  //  GLdouble dd_prev = cm->dd;

  if (CAVEgetbutton(CAVE_HKEY)) {
    //		cm->runstate = 0;

    //	show_help();

  } else if (CAVEgetbutton(CAVE_AKEY)) {
    if(cm->inc <= 0&&cm->runstate==1){
      cm->inc = 1;
    }
    if (cm->runstate == 0 && !cm->is_acc) {
      cm->is_acc = true;
      cout << "is_acc: " << is_acc_prev << " -> " << cm->is_acc << endl;
    }
  } else if (CAVEgetbutton(CAVE_QKEY)) {
    if(cm->inc > 0&&cm->runstate==1){
      cm->inc = -1;
    }
    if (cm->runstate == 0 && !cm->is_dec) {
      cm->is_dec = true;
      cout << "is_dec: " << is_dec_prev << " -> " << cm->is_dec << endl;
    }
  } else if (CAVEgetbutton(CAVE_SKEY)) {
    if (CAVEgetbutton(CAVE_ZKEY)) {
      /* s */
      cm->scale *= SCALE_UNIT;
      cout << "scale: " << scale_prev << " -> " << cm->scale << endl;
    } else {
      /*z_s*/
      cm->scale /= SCALE_UNIT;
      cout << "scale: " << scale_prev << " -> " << cm->scale << endl;
    }
  } else if (CAVEgetbutton(CAVE_RKEY)) {
    if (!CAVEgetbutton(CAVE_ZKEY)) {
      /*z_r */
      cm->radius *= SCALE_UNIT;
      cout << "radius: " << radius_prev << " -> " << cm->radius << endl;
    } else {
      /* r */
      cm->radius /= SCALE_UNIT;
      cout << "radius: " << radius_prev << " -> " << cm->radius << endl;
    }
  } else if (CAVEgetbutton(CAVE_XKEY)) {
    if (CAVEgetbutton(CAVE_ZKEY)) {
      /*x*/
      cm->phi += 0.03;
      cm->phi += 3;
      cout << "phi: " << phi_prev << " -> " << cm->phi << endl;
    } else {
      /*z_x*/
      cm->phi -= 0.03;
      cm->phi -=3;
      cout << "phi: " << phi_prev << " -> " << cm->phi << endl;
    }
  } else if (CAVEgetbutton(CAVE_WKEY)) {
//     if (CAVEgetbutton(CAVE_CTRLKEY)) {
//       /* y */
//       cm->theta += 0.03;
//       cm->theta += 3;
//       cout << "theta: " << theta_prev << " -> " << cm->theta << endl;
//     } else {
//       /*z_y */
//       cm->theta -= 0.03;
//       cm->theta -= 3;
//       cout << "theta: " << theta_prev << " -> " << cm->theta << endl;
//     }
    // 	} else if (CAVEgetbutton(CAVE_MKEY)) {
    // 		if (!CAVEgetbutton(CAVE_CTRLKEY)) {
    // 			/* U */
    //  			cm->dx += cm->dd;
    // 			cout << "dx: " << dx_prev << " -> " << cm->dx << endl;
    // 		} else {
    // 			/* u */
    // 			cm->dx -= cm->dd;
    // 			cout << "dx: " << dx_prev << " -> " << cm->dx << endl;
    // 	}
    // 	} else if (CAVEgetbutton(CAVE_NKEY)) {
    // 		if (!CAVEgetbutton(CAVE_CTRLKEY)) {
    // 			/* N */
    // 			cm->dy += cm->dd;
    // 			cout << "dy: " << dy_prev << " -> " << cm->dy << endl;
    // 		} else {
    // 			/* n */
    // 			cm->dy -= cm->dd;
    // 			cout << "dy: " << dy_prev << " -> " << cm->dy << endl;
    // 		}
    //	} else if (CAVEgetbutton(CAVE_EKEY)) {
    //		if (!CAVEgetbutton(CAVE_CTRLKEY)) {
    //			/* T */
    //			cm->dd *= 1.3;
    //			cout << "dd: " << dd_prev << " -> " << cm->dd << endl;
    //		} else {
    //			/* t */
    //			cm->dd /= 1.3;
    //			cout << "dd: " << dd_prev << " -> " << cm->dd << endl;
    //		}
  }else if(CAVEgetbutton(CAVE_CKEY)){

    cm->char_state = 1;
    if(CAVEgetbutton(CAVE_ZKEY))
      cm->char_state = 0;
  } else if (CAVEgetbutton(CAVE_PERIODKEY)) {
    /* . */
    showstep(1);
  } else if (CAVEgetbutton(CAVE_COMMAKEY)) {
    /* , */
    showstep(-1);
  }else if(CAVEgetbutton(CAVE_PKEY)){
    cm->binary_state = ARROW;
  }else if(CAVEgetbutton(CAVE_OKEY)){
    cm->binary_state = KINETIC;
  }else if(CAVEgetbutton(CAVE_IKEY)){
    cm->binary_state = POTENTIAL;
  }else if(CAVEgetbutton(CAVE_UKEY)){
    cm->binary_state = GRAVITATIONALLY_BOUND;
  }else if(CAVEgetbutton(CAVE_YKEY)){
    cm->binary_state = LINE;
  }else if(CAVEgetbutton(CAVE_EKEY)){
    cm->binary_state = ARROW_AND_GRAVITATIONALLY_BOUND;
  
  }else if(CAVEgetbutton(CAVE_TKEY)){
    cm->binary_state = NOTHING;
  }
}

void UI::Joystick(void)
{
  Common *cm = Common::GetInstance();
  if (CAVEButtonChange(3) == 1) {
    /*
      stop -> run run
      run-> stop
    */
    cm->runstate = (cm->runstate == 1) ? 0 : 1;
  } else if (CAVEBUTTON2 == 1) {
    if (CAVEButtonChange(2) == 0) {
      //  cm->beam_flag = true;
      cm->inc = -1;
    }
  } else if (CAVEButtonChange(2) == -1) {
    //    cm->beam_flag = false;
      cm->inc = 1;
  }

  if(CAVEBUTTON1==1){
    if(CAVEButtonChange(1) == 1){
      //      cm->beam_clear_flag = true;
    }
  }else if(CAVEButtonChange(1) == -1){
    //    cm->beam_clear_flag = false;
    cm->button_has_pressed();
  }
}
