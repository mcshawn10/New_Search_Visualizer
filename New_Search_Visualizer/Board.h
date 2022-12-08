#pragma once
#include "stl_inc.h"
#include "raylib.h"
#include "Cell.h"
#include "Button.h"


class Board
{

private:

	int width;
	int height;
	int rows;
	int cols;
	int fps;
	

	Button start_button;
	Button goal_button;
	Button clear_board;
	Button clear_search;
	Button D_button;
	Button BFS_button;

public:

	Board();
	bool found;
	Cell* start;
	Cell* goal;
	Cell** blocks;

	void draw_board();
	pair<int, int> get_pos();
	
	void draw_obstacles(pair<int,int> p);
	void CLEAR_BOARD();
	void CLEAR_SEARCH();
	void find_path();
	void BreadthFirstSearch();
	void Dijkstra();
	void set_start();
	void set_goal();


	void RUN();
	~Board();

};