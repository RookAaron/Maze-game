#include "my_library.h"


bool Bot::Move_valid(string direction, vector<vector<Cell>> cells, vector<int> facts)
{
	// this moves the bot to a new cell
	int width = facts[0];
	int height = facts[1];

	if (direction == "right" && x_pos + 1 == width)
	{
		return false;
	}
	if (direction == "up" && y_pos == 0)
	{
		return false;
	}
	if (direction == "left" && x_pos == 0)
	{
		return false;
	}
	if (direction == "down" && y_pos + 1 == height)
	{
		return false;
	}

	if (direction == "right" && cells[y_pos][x_pos].wall == true)
	{
		return false;
	}
	if (direction == "up" && cells[y_pos][x_pos].ceil == true)
	{
		return false;
	}
	if (direction == "left" && cells[y_pos][x_pos-1].wall == true)
	{
		return false;
	}
	if (direction == "down" && cells[y_pos+1][x_pos].ceil == true)
	{
		return false;
	}

	if (direction == "right" && cells[y_pos][x_pos+1].centre == bot_ID)
	{
		return false;
	}
	if (direction == "up" && cells[y_pos-1][x_pos].centre == bot_ID)
	{
		return false;
	}
	if (direction == "left" && cells[y_pos][x_pos-1].centre == bot_ID)
	{
		return false;
	}
	if (direction == "down" && cells[y_pos+1][x_pos].centre == bot_ID)
	{
		return false;
	}
	
	return true;
}

void Bot::Move(string direction)
{
	if (direction == "right")
	{
		x_pos++;
	}
	if (direction == "up")
	{
		y_pos--;
	}
	if (direction == "left")
	{
		x_pos--;
	}
	if (direction == "down")
	{
		y_pos++;
	}
}

void Bot::set_pos(int x, int y)
{
	x_pos = x;
	y_pos = y;
}

vector<int> Bot::get_pos()
{
	vector<int> p;
	p.push_back(x_pos);
	p.push_back(y_pos);

	return p;
}