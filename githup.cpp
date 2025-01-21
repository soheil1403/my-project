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
// حرکت بازیکن
void movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;
    
    switch (direction) {
        case 'w': newX--; break;
        case 's': newX++; break;
        case 'a': newY--; break;
        case 'd': newY++; break;
    }
    
    if (newX >= 1 && newX <= HEIGHT && newY >= 1 && newY <= WIDTH) {
        if (grid[newX][newY] != CONCRETE && grid[newX][newY] != BRICK && grid[newX][newY] != ENEMY) {
            if ((playerX + playerY) % 2 == 0) {
              grid[playerX][playerY] = '-';
             } else {
              grid[playerX][playerY] = '_';
             }

            playerX = newX;
            playerY = newY;
            grid[playerX][playerY] = PLAYER;
            moveCount++;  // افزایش تعداد حرکت‌ها
    }
    }
}
// قرار دادن بمب
void placeBomb() {
    bombs.push_back({playerX, playerY, 2, true});
    grid[playerX][playerY] = BOMB;
    bombCount++;  //افزایش  بمبا
}
// آپدیت بمب‌ها
void updateBombs() {
    for (int i = 0; i < bombs.size(); i++) {
        if (bombs[i].active) {
            bombs[i].moveCount--;
            if (bombs[i].moveCount == 0) {
                int x = bombs[i].x;
                int y = bombs[i].y;
                bombs[i].active = false;
                
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 1 && nx <= HEIGHT && ny >= 1 && ny <= WIDTH) {
                            if ((grid[nx][ny] == BRICK || grid[nx][ny] == ENEMY) && grid[nx][ny] != CONCRETE) {
                                if ((nx + ny) % 2 == 0) {
                                grid[nx][ny] = '-';
                                } else {
                              grid[nx][ny] = '_';
                              }
                            }
                        }
                    }
                }
            }
        }
    }
}