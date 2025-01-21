#include <iostream>
#include <conio.h>  // برای getch()
#include <vector>
#include <cstdlib>  // برای rand()
#include <ctime>    // برای time()
using namespace std;

const int WIDTH = 10;  // عرض نقشه
const int HEIGHT = 10; // ارتفاع نقشه
char EMPTY = ' ';
char PLAYER = 'S';
char BOMB = 'B';
char BRICK = 'Z';
char CONCRETE = 'X';
char ENEMY = 'E';
char EXIT = 'G';  // دروازه خروج
char BORDER = '*'; // مرز نقشه

struct Bomb {
    int x, y;
    int moveCount;
    bool active;
};

int playerX = 1, playerY = 1; // شروع بازیکن توی نقشه 
vector<Bomb> bombs;
char grid[HEIGHT + 2][WIDTH + 2]; // +2 برای مرزهای بالا و پایین