#ifndef _UI_H_
#define _UI_H_

#include "common.h"

class UI {
public:
	static UI *GetInstance() {
		static UI ui;
		return &ui;
	}

	void Navigation(void);
	void Keyboard(void);
	void Joystick(void);

private:
	UI() {}
	UI(const UI& obj) {}
	UI& operator=(const UI& obj);

	void SelectParticle();
	void showstep(int direction);
//	void show_help(void);
};

#endif
