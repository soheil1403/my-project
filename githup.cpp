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

// تابع ایجاد نقشه با مرز و عناصر
void generateMap() {
    srand(time(0));  
    
    // تغییرات بسته به سطح سختی
    int enemyChance = 10 + 5 * difficultyLevel;  // افزایش  دشمن با سختی
    int brickChance = 15 + 5 * difficultyLevel;  // افزایش دیوار آجری با سختی
    int concreteChance = 10 + 3 * difficultyLevel;  // افزایش  بتنی با سختی
    
    for (int i = 0; i < HEIGHT + 2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1) {
                grid[i][j] = BORDER; // ایجاد مرز دور نقشه
            } else if (i == 1 && j == 1) {
                grid[i][j] = PLAYER; // موقعیت شروع بازیکن
            } else if (i == HEIGHT && j == WIDTH) {
                grid[i][j] = EXIT; // مکان ثابت دروازه خروج
            } else if (rand() % 100 < brickChance) {
                grid[i][j] = BRICK; // احتمال دیوار آجری
            } else if (rand() % 100 < concreteChance) {
                grid[i][j] = CONCRETE; // احتمال دیوار بتنی
            } else if (rand() % 100 < enemyChance) {
                grid[i][j] = ENEMY; // احتمال دشمن
            } else {
                if ((i + j) % 2 == 0) {
               grid[i][j] = '-';
              } else {
              grid[i][j] = '_';
               }
                   // الگوی خانه خالی
            }
        }
    }
}

// تابع نمایش نقشه
void printGrid() {
    system("cls");//پاک کردن صفحه 
    for (int i = 0; i < HEIGHT +  2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            cout << grid[i][j] << ' ' ;
        }
        cout << endl;
}
}