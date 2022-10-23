#include <iostream>
#include <conio.h>//for _kbhit() and _getch()
#include <windows.h>//for including sleep

using namespace std;

bool gameOver;
int width = 9;
int height = 9;
int x, y, fruitX, fruitY, score;
int tailX[400], tailY[400];//koordinate segmenata repa, ova dva reda idu u paru
int nTail;//duzina repa: width * height - 1; -1 jer ne racunamo glavu zmije
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};//all possible directions for snake to go
eDirecton dir;

void Setup(){
    gameOver = false;
    dir = STOP;//snake is not moving at first
    x = width / 2;//starting x position for snake
    y = height / 2;//starting y position for snake
    fruitX = rand() % width;//random generated positions for the fruit
    fruitY = rand() % height;//from 0 to height-1
    score = 0;
    nTail = 0;//pocetna duzina repa je da nema repa
}
void Draw(){
    system("cls");//clears console
    for(int i = 0; i < width + 2; i++)//printing the top border
        cout << "\xFE";
    cout << endl;

    //printing all between top and bottom border
    for(int i = 0; i < height; i++){//i je visina, y koordinata
        for (int j = 0; j < width; j++){//j he duzina, x koordinata
            if(j == 0)//nacrtaj levi zid
                cout << "\xFE";

            if(i == y && j == x)//nacrtaj glavu zmije
                cout << "O";
            else if(i == fruitY && j == fruitX)//nacrtaj vocku
                cout << "@";
            else{
                    bool print = false;
                    for (int k = 0; k < nTail; k++){//za crtanje repa, ide se do duzine repa/proverava se za celu duzinu repa
                        if (tailX[k] == j && tailY[k] == i){//crta se rep
                            cout << "o";
                            print = true;
                        }
                    }
                    if(!print)//ako se nije nacrtala glava, vocka a ni rep, crta se prazno mesto
                        cout << " ";
                }

            if(j == width - 1)//nacrtaj desni zid
                cout << "\xFE";
        }
        cout << endl;//prelazak u red ispod
    }

    for(int i = 0; i < width+2; i++){//printing the bottom border
        cout << "\xFE";
    }
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input(){
    if(_kbhit()){//_kbhit() vraca true ako je neki taster pritisnut
        switch (_getch()){//_getch() vraca vrednost tastera koji je _kbhit() detektovao
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic(){
    int prevX = tailX[0];//prethodna x koordinata repa je prvi segment repa (tailX[0] na pocetku nije inicijalizovan) O F
    int prevY = tailY[0];//                                                                                            OF
    int prev2X, prev2Y;//pomocne promenljive                                                                            O
    tailX[0] = x;//pocetne koordinate repa su koordinate glave zmije                                                    oO
    tailY[0] = y;
    for(int i = 1; i < nTail; i++){//krecemo od 1 jer vec imamo tailX[0], tailY[0]
        prev2X = tailX[i];//ovo je prvo neka bzvz vrednost, posle je tailX[i] = prevX
        prev2Y = tailY[i];
        tailX[i] = prevX;//trenutni deo repa (tailX[i]) je jednak prethodnom delu repa: prevX = tailX[0], prevX = prev2X
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if (x > width || x < 0 || y > height || y < 0)//when snake hits the walls, the game ends
    //  gameOver = true;

    if(x >= width)//ako zmija predje bocne zidove, pojavice se na suprotnoj strani
        x = 0;
    else if(x < 0)
        x = width - 1;
    if(y >= height)//ako zmija predje gornji ili donji zid, pojavice se na suprotnoj strani
        y = 0;
    else if(y < 0)
        y = height - 1;

    for(int i = 0; i < nTail; i++)
        if(tailX[i] == x && tailY[i] == y)//ako glava zmije udari u rep, igra je gotova
            gameOver = true;
//NAPRAVITI DA SE KOORDINATE VOCKE NE MOGU POKLAPATI SA KOORDINATAMA REPA
    if (x == fruitX && y == fruitY){//ako se koordinate glave zmije poklope sa koordinatama vocke
        score ++;
        fruitX = rand() % width;//posto je zmija pojela vocku, generisi nove koorinate za vocku
        fruitY = rand() % height;
        nTail++;//uvecaj rep jer si pojeo vocku

        for(int i = 0; i < nTail; i++){//JEL OVO DOBRO??????????????
            if(fruitX == tailX[i] || fruitY == tailY[i]){
                fruitX = rand() % width;
                fruitY = rand() % height;
                nTail++;
            }
        }
    }
}
int main()
{
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(20); //Sleep(milliseconds) - ostane u while petlji jos toliko milisekundi
    }

    return 0;
}
