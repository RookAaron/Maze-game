#include "my_library.h"

void Level::Generate_Level(int w, int h, int s, int r, int bs)
{
	// creates the maze and adds it to the vector

	// sets facts for the maze
	maze.Set_Maze_facts(w, h, s, r, bs);
	maze.Generate_Maze();
	maze.cells[0][0].centre = user;
	player.bot_ID = user;
}

void Level::Display()
{
	// allows the game to display the maze
	set_cursor_position();
	cout << "Size: " << maze.width << "x" << maze.height
		<< "\t"
		<< "Seed: " << maze.seed
		<< "\t"
		<< "Spawn rate: " << maze.spawn_rate
		<< "\t"
		<< "Bot speed: " << maze.bot_speed
		<< endl << endl
		<< "Score: " << score
		<< endl
		<< "Number of bots: " << enemies.size()
		<< endl << endl;
	maze.Display_Maze();
}

void Level::Add_Bot()
{
	Bot b;

	vector<int> pos = maze.Add_Enemy_Pos();

	if (enemies.size() == 0) { pos = { maze.width - 1, maze.height - 1 }; }

	if (pos[0] != -1 && pos[1] != -1)
	{
		b.set_pos(pos[0], pos[1]);
		b.bot_ID = enemy;
		enemies.push_back(b);
		maze.cells[pos[1]][pos[0]].centre = enemy;
	}

	last_bot_added = system_clock::now();
}

void Level::Score_check()
{
	if (aim == "E" && player.get_pos()[0] == maze.Get_Maze_facts()[0] - 1)
	{
		aim = "W";
		score++;
	}
	else if (aim == "W" && player.get_pos()[0] == 0)
	{
		aim = "E";
		score++;
	}
}

Bot Level::Move(string direction, Bot b)
{
	int x_pos = b.get_pos()[0];
	int y_pos = b.get_pos()[1];
	maze.cells[y_pos][x_pos].centre = " ";

	b.Move(direction);
	x_pos = b.get_pos()[0];
	y_pos = b.get_pos()[1];
	maze.cells[y_pos][x_pos].centre = b.bot_ID;

	b.last_move = system_clock::now();

	return b;
}

void Level::Enemy_Move(int e)
{
	vector<string> directions;

	if (player.get_pos()[1] < enemies[e].get_pos()[1]) { directions.push_back("up"); }
	else if (player.get_pos()[1] > enemies[e].get_pos()[1]) { directions.push_back("down"); }
	if (player.get_pos()[0] < enemies[e].get_pos()[0]) { directions.push_back("left"); }
	else if (player.get_pos()[0] > enemies[e].get_pos()[0]) { directions.push_back("right"); }

	for (int i = 0; i < directions.size(); i++)
	{
		if (enemies[e].Move_valid(directions[i], maze.cells, maze.Get_Maze_facts()))
		{
			enemies[e] = Move(directions[i], enemies[e]);
			break;
		}
	}
}


void Level::Gameloop()
{
	bool playing = true;
	string user_key = "null";

	Add_Bot();

	Display();
	system("PAUSE");
	Display();
	cout << "                                " << endl;

	last_bot_added = system_clock::now();

	while (playing)
	{
		Display();

		user_key = get_key_pressed();

		if (user_key == "exit") { break; }

		else if (user_key == "pause")
		{
			cout << endl << "Game paused!!!" << endl;
			system("PAUSE");
			Display();
			cout << endl << "              " << endl;
			cout << "                                " << endl;

		}
		
		else if (user_key != "null")
		{
			if (player.Move_valid(user_key, maze.cells, maze.Get_Maze_facts()))
			{
				player = Move(user_key, player);
			}
		}

		Score_check();

		for (int i = 0; i < enemies.size(); i++)
		{
			if (time_differnece(enemies[i].last_move, system_clock::now()) > (maze.bot_speed*100) )
			{
				Enemy_Move(i);
			}
			if (enemies[i].get_pos() == player.get_pos())
			{
				playing = false;
				break;
			}
		}

		if (time_differnece(last_bot_added, system_clock::now()) > (maze.spawn_rate * 1000))
		{
			Add_Bot();
		}
	}

	while (get_key_pressed() != "null") {}

	cout << endl << "GAME OVER!" << endl;
	cout << "Final score of  " << score << endl;

	system("PAUSE");
}