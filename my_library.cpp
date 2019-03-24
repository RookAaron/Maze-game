#include "my_library.h"

vector<vector<int>> Shuffle(vector<vector<int>> list)
{
	int size = list.size();

	vector<vector<int>> new_list(size, vector<int>(2));

	vector<int> index_used(size);

	int index_num = 0;

	while (index_num < size)
	{
		int rand_index = random_num(0,size-1);

		if (index_used[rand_index] == 0)
		{
			new_list[index_num][0] = list[rand_index][0];
			new_list[index_num][1] = list[rand_index][1];

			index_used[rand_index] = 1;
			index_num++;
		}
	}
	return new_list;
}

int random_num(int min, int max)
{
	// picks a random number between and including min and max
	int r;

	do {
		r = rand() % (max + 1);
	} while (r < min || r > max); // this will loop until the correct value is reached

	return r;
}

// these will return either the min or max of two integers
int Max(int a, int b)
{
	if (a >= b) { return a; }
	if (a <= b) { return b; }
	return 0;
}
int Min(int a, int b)
{
	if (a >= b) { return b; }
	if (a <= b) { return a; }
	return 0;
}

void set_cursor_position()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
}

void set_window_size(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, width, height, TRUE);

	ShowConsoleCursor(false);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int time_differnece(time_point<system_clock> start, time_point<system_clock> end)
{
	return duration_cast<milliseconds>(end - start).count();
}

string get_key_pressed()
{
	for (int i = 0; i < number_of_keys; i++)
	{
		int key = KEYS_ID[i];
		if (GetAsyncKeyState(key) & 1)
		{
			return KEYS_INFO[i];
		}
	}

	return "null";
}