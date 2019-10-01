#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <algorithm>

#define SIZE_X 40
#define SIZE_Y 20
#define WINLEN 11
#define STIME 100

using namespace std;

void movePlayer(int x1, int y1);
int goUp(int i, int j);
int goLeft(int i, int j);
int goDown(int i, int j);
int goRight(int i, int j);
void move();
void food();
void checkFood(int i, int j);
void showLen();
bool winCheck();
void finish();

char map[SIZE_Y][SIZE_X];
vector<int> col;
vector<vector<int>> body;
int len = 1;
int tempLen = 1;
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
                cout << (char)219 << (char)219 ;

            }else if(map[i][j] == ' '){
                cout << "  ";
            }else if(map[i][j] == 'p'){
                cout << " o";
            }else if(map[i][j] == 'P'){
                cout << " O";
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
    map[i][j] = 'P';
    col.push_back(i);
    col.push_back(j);
    body.push_back(col);
    printMap();
    movePlayer(i, j);
}


void movePlayer(int i, int j){
    char get_key;
    bool win = false;
    while(!winCheck()){
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
    col.clear();
    col.push_back(i);
    col.push_back(j);
    checkFood(i, j);
    move();

  //  cout <<" i: " << body[0][0] << " j: " << body[0][1] << endl;

    printMap();
    showLen();
    Sleep(STIME);
    return i;
}

int goLeft(int i, int j){
    j--;
    col.clear();
    col.push_back(i);
    col.push_back(j);
    checkFood(i, j);
    move();

  //  cout <<" i: " << body[0][0] << " j: " << body[0][1] << endl;

    printMap();
    showLen();
    Sleep(STIME);
    return j;
}

int goDown(int i, int j){
    i++;
    col.clear();
    col.push_back(i);
    col.push_back(j);
    checkFood(i, j);
    move();

   // cout <<" i: " << body[0][0] << " j: " << body[0][1] << endl;

    printMap();
    showLen();
    Sleep(STIME);
    return i;
}

int goRight(int i, int j){
    j++;
    col.clear();
    col.push_back(i);
    col.push_back(j);
    checkFood(i, j);
    move();

//    cout <<" i: " << body[0][0] << " j: " << body[0][1] << endl;

    printMap();
    showLen();
    Sleep(STIME);
    return j;
}

void move(){
    if(tempLen != len){
        //body.pop_back();
        body.push_back(col);
        tempLen = len;
    }else{
        body.pop_back();
        body.push_back(col);
    }
    rotate(body.begin(), body.begin()+(len-1), body.end());
    for(int i=0 ; i<len ; i++){
        if(i == 0){
            map[body[0][0]][body[0][1]] = 'P';
        }else{
            map[body[i][0]][body[i][1]] = 'p';
        }
    }

}

void setFood(int i, int j){
    foodI = i;
    foodJ = j;
    map[foodI][foodJ] = 'f';
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

    start_pos = {85, 5};
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hOut, start_pos);

    cout << "Your Point: " << len-1;
}

bool winCheck(){
    if(len == WINLEN ){
        win = true;
    }
    return win;
}

void finish(){
    printMap();

    if(win){
        cout << "!*!*!*!    You Win    !*!*!*! \n" << endl;
    }else{
        cout << "GAME OVER" << endl;
    }
}

int main(){
    system("color 8f");
    cout<<"You Can Move Your Snake With (W , A , S , D)\n"<<endl;
    cout<<"Eat 10 Food To Win :)\n"<<endl;
    cout<<"Have A Good Game\n\n"<<endl;
    cout<<"* Press Enter To Start *"<<endl;
    cin.get();
    system("cls");

    system("color 0b");

    setBorder();
    setFood(10,15);
    setPlayer(10,10);
    finish();

    char z;
        do{
            cout<<"Do You Want To Play Again? (y / n)"<<endl;
            z = _getch();

            while(z!='y' && z!='n'){
                z = _getch();
            };

            if (z == 'y') {
                system("cls");

                system("color 0b");
                col.clear();
                body.clear();
                len = 1;
                tempLen = 1;
                win = false;
                setBorder();
                setFood(10,15);
                setPlayer(10,10);
                finish();
            }
            else{
                cout<<"\n    Thanks For Playing ... \n\n** Press 'ENTER' to EXIT **"<<endl;
                cin.get();
            }
        }while(z!='n');


    return 0;
}
