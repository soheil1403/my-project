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

int moveCount = 0;  // تعداد حرکت‌ها
int bombCount = 0;  // تعداد بمب‌های استفاده‌شده
time_t startTime, endTime;  // زمان شروع و پایان بازی

// متغیرهای سختی و وزن‌ها
int difficultyLevel = 1;  // 1: آسان, 2: متوسط, 3: سخت
float W_T = 0.5, W_M = 0.3, W_B = 0.2;  // وزن‌های زمان، حرکت‌ها و بمب‌ها

// توابع بازی
void generateMap();
void printGrid();
void movePlayer(char direction);
void placeBomb();
void updateBombs();
bool GameFinished();
void showMenu();
void DifficultyMenu();
void showHelp();
void playGame();
float calculateScore(int timeTaken, int moves, int bombsUsed);