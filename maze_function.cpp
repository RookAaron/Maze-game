#include "my_library.h"


void Maze::Set_Maze_facts(int w, int h, int s, int r, int bs)
{
	// takes in the maze facts and sets them to the values in the class
	width = w;
	height = h;
	// if there is no seed value, use the current time as the seed
	if (s != 0) { seed = s; }
	else { seed = time(0); }
	spawn_rate = r;
	bot_speed = bs;
}


void Maze::Walk(int x, int y)
{
	// this is the recursive function for the recursive backtracking algorithm

	cells[y][x].centre = " "; // sets the cell centre as visited

	// gets the values of all adjecent cells and shuffles it
	vector<vector<int>> adjacent_cells(4, vector<int>(2));
	adjacent_cells[0] = { x, y + 1 };
	adjacent_cells[1] = { x, y - 1 };
	adjacent_cells[2] = { x - 1, y };
	adjacent_cells[3] = { x + 1, y };
	adjacent_cells = Shuffle(adjacent_cells);

	// for every adjectent cell go through this method
	for (int i = 0; i < adjacent_cells.size(); i++)
	{
		// gets x,y values for cells
		int new_x = adjacent_cells[i][0];
		int new_y = adjacent_cells[i][1];

		// if the cell is not valid within the size grid, continue
		if (new_x < 0 || new_y < 0 || new_x >= width || new_y >= height) { continue; }
		// if cell is already visited, continue
		if (cells[new_y][new_x].centre == " ") { continue; }

		// otherwise remove path for either the new x or the new y value
		if (new_x == x)
		{
			cells[Max(new_y, y)][x].ceil = false;
		}
		if (new_y == y)
		{
			cells[y][Min(new_x, x)].wall = false;
		}

		// call the function with the new values
		Walk(new_x, new_y);
	}
}


void Maze::Recursive_Backtracking()
{
	// this sets up all the valus needed for the code to generate the maze

	srand(seed);

	cells.resize(height); // corrects the cell size

	// sets each cell up with the correct values
	for (int h = 0; h < height; h++)
	{
		cells[h].resize(width);

		for (int w = 0; w < width; w++)
		{
			cells[h][w].x_pos = w;
			cells[h][w].y_pos = h;
		}
	}
	// calls function to create maze
	Walk(0, 0);
}


void Maze::Generate_Maze()
{
	// creates maze
	Recursive_Backtracking();

	// this section will remove random walls to allow cycles within the maze

	for (int w_pos = 0; w_pos < width; w_pos++)
	{
		for (int h_pos = 0; h_pos < height; h_pos++)
			{
			if (random_num(0, 2) == 0) { continue; }

			else if (h_pos == height - 1 || h_pos == 0 || w_pos == width - 1) { continue; }

			else if (cells[h_pos][w_pos].wall == false) { continue; }

			else if (cells[h_pos][w_pos].ceil == false && cells[h_pos][w_pos + 1].ceil && cells[h_pos - 1][w_pos].wall) { continue; }

			else if (cells[h_pos + 1][w_pos].ceil == false && cells[h_pos + 1][w_pos].wall && cells[h_pos + 1][w_pos + 1].ceil) { continue; }

			else
			{
				cells[h_pos][w_pos].wall = false;
			}
		}
	}
}


vector<int> Maze::Add_Enemy_Pos()
{
	int w_pos;
	int h_pos;
	int test_h;
	int test_w;
	int c = 0;

	while (c < 100)
	{
		c++;

		w_pos = random_num(0, width - 1);
		h_pos = random_num(0, height - 1);

		bool close = false;
		for (int h = -2; h <= 2; h++)
		{
			test_h = h_pos + h;
			if (test_h < 0 || test_h >= height) { continue; }

			for (int w = -2; w <= 2; w++)
			{
				test_w = w_pos + w;
				if (test_w < 0 || test_w >= width) { continue; }

				if (cells[test_h][test_w].centre != " ") { close = true; }
			}
		}

		if (close == false)
		{
			return vector<int> {w_pos, h_pos};
		}
	}
	return vector<int> {-1, -1};
}


vector<int> Maze::Get_Maze_facts()
{
	vector<int> facts;
	facts.push_back(width);
	facts.push_back(height);
	facts.push_back(seed);
	facts.push_back(spawn_rate);
	facts.push_back(bot_speed);

	return facts;
}


void Maze::Display_Maze()
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			// output the entire top row
			cout << " ";
			if (cells[h][w].ceil == true) { cout << "--"; }
			else { cout << "  "; }
		}
		cout << " " << endl << "|";
		for (int w = 0; w < width; w++)
		{
			// output the entire bottom row
			cout << cells[h][w].centre << " ";
			if (cells[h][w].wall == true) { cout << "|"; }
			else { cout << " "; }
		}
		cout << endl;
	}
	for (int w = 0; w < width; w++)
	{
		// adds in bottom row
		cout << " --";
	}
	cout << endl;
}