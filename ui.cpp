#include "ui.h"
#include "Visualize.h"

void UI::Navigation(void) {
	/*
	 float wand_vec[3];
	 //float jx = CAVE_JOYSTICK_X;
	 //float jy = CAVE_JOYSTICK_Y;
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
	 */
}

//void UI::showstep(int direction)
//{
//  Common *cm = Common::GetInstance();
//  cm->runstate = 0;
//  int inc_prev = cm->inc;
//  if (cm->inc < 0)
//    cm->inc = -cm->inc;
//  if (cm->inc == 0)
//    cm->inc = 1;
//  if (direction < 0)
//    cm->inc = -cm->inc;
//  cout << "Step direction: " << direction << "  inc: " << inc_prev << " -> " << cm->inc << endl;
//  //	step();
//}

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

void UI::Keyboard(unsigned char key, int x, int y) {
	Common *cm = Common::GetInstance();
	Visualize vo = new Visualize();
	bool is_acc_prev = cm->is_acc;
	bool is_dec_prev = cm->is_dec;
	GLdouble scale_prev = cm->scale;
	GLdouble radius_prev = cm->radius;
	GLdouble phi_prev = cm->phi;
	GLdouble theta_prev = cm->theta;
	//  GLdouble dx_prev = cm->dx;
	//  GLdouble dy_prev = cm->dy;
	//  GLdouble dd_prev = cm->dd;
	vo.SetState(key);
}

//void UI::Joystick(void)
//{
//  Common *cm = Common::GetInstance();
//  if (CAVEButtonChange(3) == 1) {
//    /*
//      stop -> run run
//      run-> stop
//    */
//    cm->runstate = (cm->runstate == 1) ? 0 : 1;
//  } else if (CAVEBUTTON2 == 1) {
//    if (CAVEButtonChange(2) == 0) {
//      cm->beam_flag = true;
//    }
//  } else if (CAVEButtonChange(2) == -1) {
//    cm->beam_flag = false;
//  }
//
//  if(CAVEBUTTON1==1){
//    if(CAVEButtonChange(1) == 1){
//      cm->beam_clear_flag = true;
//    }
//  }else if(CAVEButtonChange(1) == -1){
//    cm->beam_clear_flag = false;
//  }
//}
