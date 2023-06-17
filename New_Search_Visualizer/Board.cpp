//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "raylib.h"
#include "stl_inc.h"
#include "Board.h"
#include "Button.h"
#include <memory>
#include <cassert>
#include <set>
#include <limits>
#include <set>
//#include "PQ.h"
//#include <chrono>
//#include <Windows.h>


Board::Board()
{
	width = 1200;
	height = 700;
	rows = 25; // number of rows
	cols = 60; // number of columns
	fps = 60;
	
	found = false;
	start = nullptr;
	goal = nullptr;
	
	blocks = new Cell* [rows];

	start_button = Button("Start Cell", 20, 50, 300, 50);
	goal_button = Button("Goal Cell", 350, 50, 300, 50);
	clear_board = Button("Clear Board", 800, 50, 350, 50);
	clear_search = Button("Clear Search", 800, 100, 350, 50);
	D_button = Button("Dijkstra", 400, 150, 250, 50);
	BFS_button = Button("BFS", 700, 150, 250, 50);

	for (int row = 0;row<this->rows; row++)
	{
		blocks[row] = new Cell[cols];

	}

	for (int row = 0; row < this->rows; row++)
	{
		for (int col = 0; col < this->cols; col++)
		{
			
			blocks[row][col] = Cell(row, col, WHITE, "WHITE");
		}
	}

	
}

void Board::draw_board()
{
	ClearBackground(LIGHTGRAY);

	for (int r = 0; r < rows; r++) // draw grid lines
	{
		DrawLine(0, 200 + r * 20, 1200, 200 + r * 20, BLACK);
	}
	for (int c = 0; c < cols; c++)
	{
		DrawLine(c * 20, 200, c * 20, 700, BLACK);
	}

	for (int row = 0; row < this->rows; row++)
	{
		for (int col = 0; col < this->cols; col++)
		{
			blocks[row][col].display_cell();
		}
	}
}

pair<int, int> Board::get_pos()
{
	int r = floor((GetMouseY() - 200) / 20);
	int c = floor(GetMouseX() / 20);

	return std::make_pair(r, c);
}

void Board::set_start()
{
	int r = rand() % 25;
	int c = rand() % 60;


	start = &blocks[r][c];
	start->parent = nullptr;

	start->set_color(GREEN, "GREEN");
	
	start->display_cell();
}

void Board::set_goal()
{
	int r = rand() % 25;
	int c = rand() % 60;

	goal = &blocks[r][c];

	goal->set_color(RED, "RED");
	
	goal->display_cell();
}

void Board::find_path()
{
	//Cell* p = new Cell(*goal);
	Cell* p = goal;
	assert(p != nullptr);
	if (found)
	{
		while (p != nullptr)
		{
			
			p->set_color(YELLOW, "YELLOW");

			p->display_cell();
			p = p->parent;
			
		}
		start->set_color(GREEN, "GREEN");
		goal->set_color(RED, "RED");
		
	}
	else
	{
		cout << "Path not found" << "\n";
	}

	//delete p;
}

void Board::draw_obstacles(pair<int,int> p)
{
	blocks[p.first][p.second].set_color(BLACK, "BLACK");
	
	blocks[p.first][p.second].display_cell();

}

void Board::CLEAR_BOARD()
{
	for (int r = 0; r < this-> rows; r++)
	{
		for (int c = 0; c < this->cols; c++)
		{
			blocks[r][c].parent = nullptr;
			blocks[r][c].Hscore = 10000;
			blocks[r][c].set_color(WHITE, "WHITE");
			blocks[r][c].display_cell();
		}
	}
}

void Board::CLEAR_SEARCH()
{
	for (int r = 0; r < this->rows; r++)
	{
		for (int c = 0; c < this->cols; c++)
		{
			string temp_color = blocks[r][c].get_color();

			if (temp_color == "SKYBLUE" || temp_color == "YELLOW")
			{
				blocks[r][c].parent = nullptr;
				blocks[r][c].set_color(WHITE, "WHITE");
				blocks[r][c].display_cell();
			}
		}
	}
}


void Board::BreadthFirstSearch()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	
	std::list <Cell*> Q; //transfered ownership? <Cell*>
	vector<Cell*> children;
	vector<Cell*> visited;
	
	/*visited and Q shouldnt be wasting space storing duplicates*/

	Q.push_back(start);

	while (!Q.empty())
	{	
		
		Cell* CURRENT = Q.front(); // invokes copy constructor or move?
		Q.pop_front();
		
		
		if (CURRENT == this->goal)
		{

			this->found = true;
			Q.clear();
		}
		
		else if (find(visited.begin(), visited.end(), CURRENT) == visited.end()) // if Current NOT in visited
		{
			visited.push_back(CURRENT);

			int r_temp = CURRENT->row;
			int c_temp = CURRENT->col;

			if (r_temp + 1 <= 24) // HOW TO ACCESS THE ORIGINAL
			{
				Cell* temp_1 = &blocks[r_temp + 1][c_temp]; // temp is uninitialized?
				children.push_back(temp_1); // COPY constructor, pass by reference

			}
			
			if (0 <= c_temp - 1)
			{
				Cell* temp_3 = &blocks[r_temp][c_temp - 1];
				children.push_back(temp_3);

			}

			if (0 <= r_temp - 1)
			{
				Cell* temp_2 = &blocks[r_temp - 1][c_temp];
				children.push_back(temp_2);

			}

			if (c_temp + 1 <= 59)
			{
				Cell* temp_4 = &blocks[r_temp][c_temp + 1];
				children.push_back(temp_4);

			}

			for (Cell* child : children)
			{

				if (child->color_string == "BLACK" || (find(visited.begin(), visited.end(), child) != visited.end()))
				{
					continue;
				}
				

				else //if (child->get_color() != "GREEN" && child->get_color() != "RED")
				{
					//if (child->parent == nullptr) { child->parent = CURRENT; }
					child->parent = CURRENT;

					if (find(Q.begin(), Q.end(), child) == Q.end()) { Q.push_back(child); } // if child not in Q
					
					child->set_color(SKYBLUE, "SKYBLUE");

					child->display_cell();
				}
				
			}


			children.clear();
			
		}
		else continue;
	}
	//find_path();

	visited.clear();
	children.clear();


}

void Board::Dijkstra()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//auto start_time = std::chrono::steady_clock::now();
	auto compare = [](Cell* mine, Cell* other) {return mine->Hscore > other->Hscore; };
	priority_queue <Cell*, vector<Cell*>, decltype(compare)> OPEN(compare);

	
	std::set <Cell*> visited;


	start->Hscore = 0;

	for (int r = 0; r < 25; r++)
	{
		for (int c = 0; c < 60; c++)
		{
			OPEN.push(&blocks[r][c]);
		}
	}

	//OPEN.push(start);

	vector <Cell*> children;

	while (!OPEN.empty())
	{
		Cell* CURRENT = OPEN.top();		
		OPEN.pop();


		//visited.push_back(CURRENT);


		if (CURRENT == goal)
		{
			found = true;
			
			break;
		}

		else if (find(visited.begin(), visited.end(), CURRENT) == visited.end()) // if Current NOT in visited
		{
			//cout << CURRENT->Hscore << " $" << endl;
			

			int r_temp = CURRENT->row;
			int c_temp = CURRENT->col;

			if (r_temp + 1 <= 24) // HOW TO ACCESS THE ORIGINAL
			{
				Cell* temp_1 = &blocks[r_temp + 1][c_temp]; // temp is uninitialized?
				children.push_back(temp_1); // COPY constructor, pass by reference

			}

			if (0 <= c_temp - 1)
			{
				Cell* temp_3 = &blocks[r_temp][c_temp - 1];
				children.push_back(temp_3);

			}

			if (0 <= r_temp - 1)
			{
				Cell* temp_2 = &blocks[r_temp - 1][c_temp];
				children.push_back(temp_2);

			}

			if (c_temp + 1 <= 59)
			{
				Cell* temp_4 = &blocks[r_temp][c_temp + 1];
				children.push_back(temp_4);

			}

			for (Cell* child : children)
			{

				//int child_dist = *start - *child;
				int weight = CURRENT->m_dist(child);
				int dist = CURRENT->m_dist(start);
				//int new_dist = child_dist + weight;

				int new_dist = CURRENT->Hscore + weight;


				//cout <<"Q size: "<< OPEN.size() << " Current: " << CURRENT->Hscore << ", new dist: " << new_dist << ", weight: " << weight << endl;
				


				if (child->color_string == "BLACK" || find(visited.begin(), visited.end(), child) != visited.end()) { continue; }

				else if (new_dist < child->Hscore && find(visited.begin(), visited.end(), child) == visited.end())
				{
					//cout << "working" << endl;
					child->Hscore = new_dist;

					child->parent = CURRENT;

					visited.insert(CURRENT);


					if (child->color_string != "RED" && child->color_string != "GREEN")
					{
						//cout << "reached" << endl;
						child->set_color(SKYBLUE, "SKYBLUE");
						child->display_cell();
					}
				}

				else continue;

			}
			children.clear();

		}
		else continue;
		
	}
	//_CrtDumpMemoryLeaks();
	visited.clear();
	children.clear();

	while (!OPEN.empty()) OPEN.pop();
	
	//find_path();

	//auto end_time = std::chrono::steady_clock::now();
	//double duration = double(std::chrono::duration_cast <std::chrono::seconds>) (end_time - start_time).count();
	//cout << duration << endl;
}


void Board::Astar()
{
	auto compare = [](Cell* mine, Cell* other) {return mine->Fscore > other->Fscore; };
	priority_queue <Cell*, vector<Cell*>, decltype(compare)> open(compare);

	//PQ open;

	std::set <Cell*> visited;


	
	for (int r = 0; r < 25; r++)
	{
		for (int c = 0; c < 60; c++)
		{
			open.push(&blocks[r][c]);
		}
	}

	start->Hscore = start->m_dist(goal);
	start->Gscore = 0;
	start->Fscore = start->Gscore + start->Hscore;
	//OPEN.push(start);

	vector <Cell*> children;

	while (!open.empty())
	{
		Cell* current = open.top();

		if (current == goal)
		{
			found = true;
			break;
		}

		else if (find(visited.begin(), visited.end(), current) == visited.end())
		{
			int r_temp = current->row;
			int c_temp = current->col;

			if (r_temp + 1 <= 24) // HOW TO ACCESS THE ORIGINAL
			{
				Cell* temp_1 = &blocks[r_temp + 1][c_temp]; // temp is uninitialized?
				children.push_back(temp_1); // COPY constructor, pass by reference

			}

			if (0 <= c_temp - 1)
			{
				Cell* temp_3 = &blocks[r_temp][c_temp - 1];
				children.push_back(temp_3);

			}

			if (0 <= r_temp - 1)
			{
				Cell* temp_2 = &blocks[r_temp - 1][c_temp];
				children.push_back(temp_2);

			}

			if (c_temp + 1 <= 59)
			{
				Cell* temp_4 = &blocks[r_temp][c_temp + 1];
				children.push_back(temp_4);

			}

			for (auto child : children)
			{

			}
		}
	}
}
void Board::RUN()
{
	InitWindow(width, height, "New Search Algorithm Visualizer");
	SetTargetFPS(fps);

	Button button_list[6] = { this->start_button, this->goal_button, this->clear_board, this->clear_search, this->D_button, this->BFS_button };

	while (!WindowShouldClose()) // while loop that controls the rest
	{
		BeginDrawing();


		draw_board();

		this->start_button.draw_box();
		this->start_button.draw_text();

		this->goal_button.draw_box();
		this->goal_button.draw_text();

		this->clear_board.draw_box();
		this->clear_board.draw_text();

		this->clear_search.draw_box();
		this->clear_search.draw_text();

		this->D_button.draw_box();
		this->D_button.draw_text();

		this->BFS_button.draw_box();
		this->BFS_button.draw_text();

		///*
		for (int i = 0; i < 6; i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), button_list[i].textbox)) button_list[i].mouseOn = true;
			else  button_list[i].mouseOn = false;
		}
		for (int i = 0; i < 6; i++)
		{
			if (button_list[i].mouseOn)
			{
				DrawRectangleLines((int)button_list[i].textbox.x, (int)button_list[i].textbox.y, (int)button_list[i].textbox.width, (int)button_list[i].textbox.height, GREEN);
			}
			else DrawRectangleLines((int)button_list[i].textbox.x, (int)button_list[i].textbox.y, (int)button_list[i].textbox.width, (int)button_list[i].textbox.height, BLACK);
		}


		// game logic



		if (IsMouseButtonPressed(0) && GetMouseY() < 200)
		{
			

			if (CheckCollisionPointRec(GetMousePosition(), button_list[0].textbox)) this->set_start();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[1].textbox)) this->set_goal();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[2].textbox)) this->CLEAR_BOARD();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[3].textbox)) this->CLEAR_SEARCH();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[4].textbox)) this->Dijkstra();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[5].textbox)) this->BreadthFirstSearch();
		}


		else if (IsMouseButtonDown(0) && GetMouseY() > 200)
		{

			pair<int,int> position = get_pos();
			draw_obstacles(position);

		}
		//*/


		EndDrawing();

	}
}


Board::~Board()
{
	cout << "Board destructed" << endl;
	delete[] blocks;
	
}





