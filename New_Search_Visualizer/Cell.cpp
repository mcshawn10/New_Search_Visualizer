#include "raylib.h"
#include "stl_inc.h"
#include "Cell.h"






Cell::Cell()
{
	this->counter++;
	this->row = 0;
	this->col = 0;
	this->parent = nullptr;
	Fscore = 0;
	Gscore = 0;
	Hscore = std::numeric_limits<int>::max();

}

Cell::Cell(int rw, int cl, Color clr, string c_s)
{
	this->row = rw;
	this->col = cl;
	this->color = clr;
	this->color_string = c_s;
}

Cell::Cell(const Cell& obj)
{
	this->size = obj.size;
	this->row = obj.row;
	this->col = obj.col;
	this->color = obj.color;
	this->color_string = obj.color_string;
	this->parent = obj.parent;
}

void Cell::set_color(Color c, string clr_str)
{
	this->color = c;
	this->color_string = clr_str;
}

string Cell::get_color() { return this->color_string; }

void Cell::display_cell()
{
	DrawRectangle(this->col * 20 + 1, this->row * 20 + 202, this->size, this->size, this->color);
}

int Cell::m_dist(Cell* other)
{
	return abs(this->row - other->row) + abs(this->col - other->col);
}

Cell& Cell::operator=(const Cell& other)
{
	this->size = other.size;
	this->counter = other.counter;
	this->row = other.row;
	this->col = other.col;
	this->color = other.color;
	this->color_string = other.color_string;
	this->parent = other.parent;

	return *this;
}

bool Cell::operator==(const Cell& other) const
{
	if (this->row == other.row && this->col == other.col && this->parent == other.parent) return true;
	else return false;
}

bool Cell::operator!=(const Cell& other) const
{
	if (this->row != other.row && this->col != other.col && this->parent != other.parent) return true;
	else return false;
}

bool Cell::operator<(const Cell& other) const { return this->counter < other.counter; }

bool Cell::operator>(const Cell& other) const { return this->counter > other.counter; }

Cell::~Cell()
{
}


