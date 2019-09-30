#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

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
int len = 1;
bool win = false;

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
    map[i][j] = 'f';
}

void food(){
    srand(time(NULL));

    int i, j;

    i = rand() % SIZE_Y - 1;
    j = rand() % SIZE_X - 1 ;

    if (map[i][j] == ' ' ){
        map[i][j] = 'f';
    }
    else{
        while(map[i][j] !=  ' '){
            i = rand() % SIZE_Y - 1;
            j = rand() % SIZE_X - 1;
        };
        map[i][j] = 'f';
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
        cout<< "YOU WIN" ;
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
