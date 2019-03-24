#ifndef IMPORTS_H
#define IMPORTS_H


/*
I am using this to hold all the imports the other header files need
this will save me having to type this for every header
*/

#include <string>		// char types
#include <iostream>		// cin, cout
#include <random>		// rand()
#include <time.h>       // time(0) get current time
#include <vector>		// going to use vectors instead of arrays
#include <windows.h>	// clear console
#include <chrono>		// high_resolution_clock::now();

// int x = rand() % 10 + 1 number between and including 1 and 10
// srand(1) -> resets the random psuedo code numbers


using namespace std;	// removes the prefix for std
using namespace chrono; // for <chrono>

#include "key_ID.h"

// ================================================
// functions
// ================================================

vector<vector<int>> Shuffle(vector<vector<int>>);

int random_num(int min, int max);

int Max(int, int);
int Min(int, int);

void set_cursor_position();

void set_window_size(int, int);

void ShowConsoleCursor(bool);

int time_differnece(time_point<system_clock>, time_point<system_clock>);

string get_key_pressed();

// ================================================
// important classes
// ================================================

struct Cell
{
	int x_pos = -1;
	int y_pos = -1;

	bool ceil = true;
	bool wall = true;

	string centre = "X";
};

class Bot
{
protected:
	int x_pos = 0;
	int y_pos = 0;

public:
	bool Move_valid(string direction, vector<vector<Cell>>, vector<int>);
	void Move(string direction);
	string bot_ID;
	void set_pos(int, int);
	vector<int> get_pos();

	time_point<system_clock> last_move = system_clock::now();
};

class Maze
{
protected:
	void Recursive_Backtracking();
	void Walk(int, int);

public:
	void Set_Maze_facts(int width, int height, int seed, int spawn_rate, int bot_speed); // this can change the maze facts for the maze info
	void Generate_Maze();
	void Display_Maze(); // can display the maze
	vector<int> Get_Maze_facts();
	vector<int> Add_Enemy_Pos();

	vector<vector<Cell>> cells;

	int width;
	int height;
	int seed;
	int spawn_rate; // how many seconds until the next one spawns
	int bot_speed;
};

class Level
{
protected:
	int difficulty = 5;

	Bot player;

	int score = 0;
	string aim = "E";

	vector<Bot> enemies;
	Maze maze;

	time_point<system_clock> last_bot_added = system_clock::now();

public:
	void Generate_Level(int, int, int, int, int);
	void Display();
	void Gameloop();
	void Add_Bot();
	void Enemy_Move(int);
	void Score_check();
	Bot Move(string, Bot);
};

#endif