#pragma once
#include "stl_inc.h"
#include "raylib.h"
#include <cstdlib>

class Cell
{
protected:

	
	
 
public:
	int size = 17;
	int counter = 0;
	int row = 0;
	int col = 0;
	int Fscore;
	int Gscore;
	int Hscore;
	Color color = WHITE;
	string color_string = "WHITE";
	Cell* parent;
	Cell();
	Cell(int rw, int cl, Color clr, string c_s);
	Cell(const Cell& obj); // copy constructor
	void set_color(Color c, string clr_str);
	string get_color();
	void display_cell();

	int m_dist(Cell* other);
	Cell& operator=(const Cell& other);
	bool operator==(const Cell& other) const;
	bool operator!=(const Cell& other) const;
	bool operator < (const Cell& other) const;
	bool operator > (const Cell& other) const;
	int operator - (Cell& other);
	~Cell();
};
