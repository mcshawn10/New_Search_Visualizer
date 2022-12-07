#include "raylib.h"
#include "stl_inc.h"
#include "Button.h"

Button::Button()
{
	mouseOn = false;
}

Button::Button(const char* t, int xp, int yp, int w, int h)
{
	title = t;

	textbox.x = xp;
	textbox.y = yp;
	textbox.width = w;
	textbox.height = h;

}


void Button::draw_box()
{
	DrawRectangleRec(textbox, WHITE);
}

void Button::draw_text()
{
	DrawText(title, (int)textbox.x + 2, (int)textbox.y, 50, MAROON);

}

Button::~Button()
{
}