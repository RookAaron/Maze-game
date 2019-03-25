#include "my_library.h"

int menu_display(vector<string> menu)
{
	system("CLS");
	int user_choice = 0;
	string user_key = "null";
	bool flash = true;
	time_point<system_clock> t = system_clock::now();

	while (user_key != "enter")
	{
		user_key = get_key_pressed();

		set_cursor_position();
		for (int i = 0; i < menu.size(); i++)
		{
			cout << endl;
			if (i != user_choice || flash)
			{
				cout << menu[i] << endl;
			}
			else
			{
				for (int j = 0; j < menu[i].length(); j++)
				{
					if (menu[i].at(j) == *"\n") { cout << "\n"; }
					cout << " ";
				}
				cout << endl;
			}
		}

		if (user_key == "up") { user_choice--; }
		if (user_key == "down") { user_choice++; }
		if (user_choice < 0) { user_choice = menu.size() - 1; }
		if (user_choice >= menu.size()) { user_choice = 0; }

		if (time_differnece(t, system_clock::now()) > 400)
		{
			if (flash == true) { flash = false; }
			else { flash = true; }
			t = system_clock::now();
		}
	}
	return user_choice;
}

vector<int> custom_level()
{
	system("CLS");
	int user_choice = 0;
	string user_key = "null";
	bool flash = true;
	time_point<system_clock> t = system_clock::now();
	int seed = time(0);

	vector<string> settings = { "Width", "Height", "Seed", "Spawn rate", "Bot speed", "Play", "return" };
	vector<int> values = { 10, 10, seed, 1, 5, 0, 0 };
	vector<vector<int>> min_max_values = { {5, 50},{5,20},{0, 2100000000},{1,60},{1,20},{0,0},{0,0} };

	while (user_key != "enter")
	{
		user_key = get_key_pressed();

		set_cursor_position();
		for (int i = 0; i < settings.size(); i++)
		{
			cout << endl;
			if (i != user_choice || flash)
			{
				cout << settings[i] << " ";
				if (i < 5) { cout << values[i]; }
				cout << endl;
			}
			else
			{
				cout << "                                  ";
				cout << endl;
			}

			if (user_key == "right" && settings[i] == settings[user_choice])
			{
				if (values[i] != min_max_values[i][1]) { values[i]++; }
			}
			if (user_key == "left" && settings[i] == settings[user_choice])
			{
				if (values[i] != min_max_values[i][0]) { values[i]--; }
			}
			if (user_key == "pause" && settings[i] == settings[user_choice])
			{
				values[i] = min_max_values[i][0];
			}
		}

		if (user_key == "up") { user_choice--; }
		if (user_key == "down") { user_choice++; }
		if (user_choice < 0) { user_choice = settings.size() - 1; }
		if (user_choice >= settings.size()) { user_choice = 0; }

		if (time_differnece(t, system_clock::now()) > 400)
		{
			if (flash == true) { flash = false; }
			else { flash = true; }
			t = system_clock::now();
		}
	}
	if (user_choice == 6) { values[5] = 1; }

	return values;
}


int main()
{
	ShowConsoleCursor(false);

	int choice = -1;
	vector<string> menu = { "PLAY", "CUSTOM LEVEL", "EXIT" };
	vector<string> difficulty = { "BEGINNER", "EASY", "INTERMEDIATE", "HARD", "EXPERT", "IMPOSSIBLE", "\nreturn" };

	int w, h, s, r, bs;

	while (1)
	{
		choice = menu_display(menu);

		if (choice == 0)
		{
			choice = menu_display(difficulty);

			w = 20; h = 10; s = 0; r = 15; bs = 5;

			if (choice == 0) { r = 25; bs = 12; }
			else if (choice == 1) { r = 20; bs = 10; }
			else if (choice == 2) {}
			else if (choice == 3) { w = 30; h = 15; bs = 4; }
			else if (choice == 4) { w = 25; h = 10; r = 10; bs = 3; }
			else if (choice == 5) { w = 40; h = 10; r = 5; bs = 2; }
			else { continue; }
		}
		else if (choice == 1)
		{
			vector<int> facts = custom_level();
			w = facts[0]; h = facts[1]; s = facts[2]; r = facts[3]; bs = facts[4];

			if (facts[5]) { continue; }
		}
		else { break; }

		system("CLS");
		set_window_size(1250, 700);
		Level play;
		play.Generate_Level(w, h, s, r, bs);
		play.Gameloop();
	}

	system("CLS");
	cout << endl << "Thank you for playing!" << endl << "Goodbye" << endl;
	Sleep(1000);
	cout << "Come back soon!";
	Sleep(10);
}