#ifndef key_ID_H
#define key_ID_H

// the user display in the maze
#define user "#"
#define enemy "X"

// this defines all the keys that the user can use within the code

// move up
#define KEY_W 0x57
// move left
#define KEY_A 0x41
// move right
#define KEY_D 0x44
// move down
#define KEY_S 0x53
// exit
#define KEY_E 0x45
// pause
#define KEY_P 0x50

#define KEYS_ID vector<int> {VK_UP, KEY_W, VK_LEFT, KEY_A, VK_RIGHT, KEY_D, VK_DOWN, KEY_S, KEY_E, KEY_P, VK_RETURN}

#define KEYS_INFO vector<string> {"up", "up", "left", "left", "right", "right", "down", "down", "exit", "pause", "enter"}

#define number_of_keys (KEYS_ID.size())

#endif