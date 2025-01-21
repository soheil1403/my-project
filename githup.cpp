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
// بررسی پایان بازی
bool GameFinished() {
    // بررسی نابودی تمام دشمن‌ها
    bool allEnemiesDestroyed = true;
    for (int i = 1; i <= HEIGHT; i++) {
        for (int j = 1; j <= WIDTH; j++) {
            if (grid[i][j] == ENEMY) {
                allEnemiesDestroyed = false;
                break;
            }
        }
    }

    // شرط پایان بازی: همه دشمنان نابود و بازیکن به خروجی برسد
    if (allEnemiesDestroyed && playerX == HEIGHT && playerY == WIDTH) {
        return true;
    }

    return false;
}

// تابع محاسبه امتیاز
float calculateScore(int timeTaken, int moves, int bombsUsed) {
    return 1000.0f / (1 + W_T * timeTaken + W_M * moves + W_B * bombsUsed);
}
// تابع نمایش منو اصلی
void showMenu() {
    char choice;
    cout << "*-*-*-*-*- Your menu *-*-*-*-*-*-" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Help" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice ?: " ;
    cin >> choice;
    
    if (choice == '1') {
        DifficultyMenu(); // نمایش منوی انتخاب سختی
    } else if (choice == '2') {
        showHelp(); // نمایش راهنما
    } else  {
        exit(0); // خروج از برنامه
     }
}
// تابع نمایش منوی انتخاب سطح سختی
void DifficultyMenu() {
    char choice;
    cout << "*-*-*-*--* Game level *-*-*-*-*--" << endl;
    cout << "1= Easy" << endl;
    cout << "2= Medium" << endl;
    cout << "3= Hard" << endl;
    cout << "Enter your choice : ";
    cin >> choice;
    
    // تنظیم سطح سختی
    switch (choice) {
        case '1':
            difficultyLevel = 1;
            break;
        case '2':
            difficultyLevel = 2;
            break;
        case '3':
            difficultyLevel = 3;
            break;
        default:
            cout << "Another choice defaulting to Easy." << endl;
            difficultyLevel = 1;
            break;
    }

    generateMap();  // ایجاد نقشه
    playGame(); // شروع بازی
}
void showHelp() {
    cout << "*-*-*-*Do you want help?*-*-*-" << endl;
     cout << "1. Use 'w', 'a', 's', 'd' keys to move the player" << endl;
    cout << "2. Use b to place a bomb." << endl;
     cout << "3. Destroy the enemies with bombs and go to the end house " << endl;
    cout << "Press any key to go back to the main menu." << endl;
    getch(); // منتظر ورودی از کاربر
    showMenu(); // بازگشت به منوی اصلی
}
// تابع اصلی بازی
void playGame() {
    char input;
    bool gameOver = false;

    startTime = time(0); // ثبت زمان شروع بازی

    while (!gameOver) {
        printGrid();
        input = getch();
        
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            movePlayer(input);
            updateBombs();
        } else if (input == 'b') {
            placeBomb();
        }

        gameOver = GameFinished(); // بررسی شرایط پایان بازی
    }
    
    endTime = time(0); // ثبت زمان پایان بازی
    int timeTaken = difftime(endTime, startTime); // محاسبه مدت زمان بازی

    // محاسبه و نمایش امتیاز
    float score = calculateScore(timeTaken, moveCount, bombCount);
    
    // نمایش نتیجه بازی
    cout << "Congratulations! You have destroyed all enemies and reached the exit!" << endl;
    cout << "Game Over!" << endl;
    cout << "Duration: " << timeTaken << " seconds" << endl;
    cout << "Your score: " << score << endl;

    // برگشت به منوی اصلی
    cout << "Press any key to return to the main menu..." << endl;
    getch(); // منتظر ورودی از کاربر
    showMenu(); // بازگشت به منوی اصلی
}