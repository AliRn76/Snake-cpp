#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <vector>

#define SIZE_X 40
#define SIZE_Y 20
#define WINLEN 4
#define STIME 100

using namespace std;

void movePlayer(int x1, int y1);
int goUp(int i, int j);
int goLeft(int i, int j);
int goDown(int i, int j);
int goRight(int i, int j);
void food();
void checkFood(int i, int j);
void showLen();
bool winCheck();
void finish();

char map[SIZE_Y][SIZE_X];
vector<int> col;
vector<vector<int>> body;
int len = 1;
bool win = false;
int foodI, foodJ;


void setBorder(){
    for(int i=0 ; i<SIZE_Y; i++){
        for(int j=0 ; j<SIZE_X; j++){
            if(i == 0 || j == 0 || i == SIZE_Y-1 || j == SIZE_X-1){
                map[i][j] = '#';
            }else{
                map[i][j] = ' ';
            }
        }
    }
}

void showConsoleCursor  (bool showFlag) {
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO     cursorInfo;
            GetConsoleCursorInfo(out, &cursorInfo);
            cursorInfo.bVisible = showFlag;
            SetConsoleCursorInfo(out, &cursorInfo);
        }

void clearScreen(){
            COORD start_pos;
            HANDLE hOut;
            start_pos = {0 , 0};
            hOut = GetStdHandle(STD_OUTPUT_HANDLE);
       //     system("cls");
            SetConsoleCursorPosition(hOut, start_pos);
            showConsoleCursor(false);
}

void setFoodPosition(){
    map[foodI][foodJ] = 'f';
}

void printMap(){
    clearScreen();
    for(int i=0 ; i<SIZE_Y; i++){
        for(int j=0 ; j<SIZE_X; j++){
            if(map[i][j] == '#'){
                cout << "##";

            }else if(map[i][j] == ' '){
                cout << "  ";
            }else if(map[i][j] == 'p'){
                cout << " P";
            }else if(map[i][j] == 'f'){
                cout << " *";
            }
        }
        cout << endl;
    }
    setBorder();
    setFoodPosition();
}


void setPlayer(int i, int j){
    map[i][j] = 'p';
    printMap();
    movePlayer(i, j);
}


void movePlayer(int i, int j){
    char get_key;
    bool win = false;
    while(!win){
        get_key = _getch();

        switch(get_key){
            case 'w':
                while(!kbhit() && !winCheck()){
                    i = goUp(i, j);
                }
                break;

            case 'a':
                while(!kbhit() && !winCheck()){
                    j = goLeft(i, j);
                }
                break;

            case 's':
                while(!kbhit() && !winCheck()){
                    i = goDown(i, j);
                }
                break;

            case 'd':
                while(!kbhit() && !winCheck()){
                    j = goRight(i, j);
                }
                break;
        }
    }
}

int goUp(int i, int j){
    i--;
    checkFood(i, j);
    map[i][j] = 'p';
    printMap();
    showLen();
    Sleep(STIME);
    return i;
}

int goLeft(int i, int j){
    j--;
    checkFood(i, j);
    map[i][j] = 'p';
    printMap();
    showLen();
    Sleep(STIME);
    return j;
}

int goDown(int i, int j){
    i++;
    checkFood(i, j);
    map[i][j] = 'p';
    printMap();
    showLen();
    Sleep(STIME);
    return i;
}

int goRight(int i, int j){
    j++;
    checkFood(i, j);
    map[i][j] = 'p';
    printMap();
    showLen();
    Sleep(STIME);
    return j;
}

void setFood(int i, int j){
    foodI = i;
    foodJ = j;
}

void food(){
    srand(time(NULL));

    foodI = rand() % SIZE_Y - 1;
    foodJ = rand() % SIZE_X - 1 ;

    while(map[foodI][foodJ] !=  ' '){
        foodI = rand() % SIZE_Y - 1;
        foodJ = rand() % SIZE_X - 1;
    }
}

void checkFood(int i, int j){
    if(map[i][j] == 'f'){
        len ++;
        food();
    }
}

void showLen(){
    COORD start_pos;
    HANDLE hOut;

    start_pos = {85, 10};
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hOut, start_pos);

    cout << "Len: " << len;
}

bool winCheck(){
    if(len == WINLEN ){
        win = true;
    }
    return win;
}

void finish(){
    if(win){
        cout << "You Win " << endl;
    }else{
        cout << "GAME OVER" << endl;
    }
}

int main(){

    setBorder();
    setFood(10,15);
    setPlayer(10,10);
    finish();


    return 0;
}
