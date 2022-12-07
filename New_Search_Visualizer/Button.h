#pragma once
#include "stl_inc.h"

class Button
{

public:
	Button();
	Button(const char* t, int xp, int yp, int w, int h);
	const char* title;
	Rectangle textbox;

	bool mouseOn;
	//void function();
	void draw_box();
	void draw_text();
	~Button();
};