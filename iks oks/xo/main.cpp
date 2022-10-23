#include <iostream>
#include <cstdlib> //for refreshing screen ( system("cls") )

using namespace std;
//THIS SECTION IS FOR THE X-O GAME CODE------------------------------------------------------------------------------------------
//windows key + r -> enter charmap for characters, advanced view->DOS western europe -> 0xDB (in c++ its "\xDB")
char field[5][5] = {'1', '\xDB', '2', '\xDB', '3', '\xDB', '\xDB', '\xDB', '\xDB', '\xDB', '4', '\xDB', '5', '\xDB', '6', '\xDB', '\xDB', '\xDB', '\xDB', '\xDB', '7', '\xDB', '8', '\xDB', '9'};
char matrix[5][5] = {'1', '\xDB', '2', '\xDB', '3', '\xDB', '\xDB', '\xDB', '\xDB', '\xDB', '4', '\xDB', '5', '\xDB', '6', '\xDB', '\xDB', '\xDB', '\xDB', '\xDB', '7', '\xDB', '8', '\xDB', '9'};
//reference matrix for reseting the game
bool gameOver = false;
char nextPlayer = 'X';//X is always first player
char input;
int counter = 0;
int scoreX = 0, scoreO = 0;
int scoreEnd;//number of wins when to end game

void Draw(){
    system("cls");//clears cmd screen
    cout << "GAME: X-O" << endl;
    cout << "Player turn: " << nextPlayer << endl;
    cout << endl;
    for(int i = 0; i < 5; i++){//i je y osa, j je x osa
        for(int j = 0; j < 5; j++){
            cout << field[i][j];//i su redovi, j su kolone
        }
        cout << endl;
    }
    cout << endl;

    cout << "\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE" << endl;
    cout << "Score X: " << scoreX << endl;
    cout << "Score O: " << scoreO << endl;
    cout << "\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE" << endl;
}

void Input(){
    cout << "Choose a number on field to put " << nextPlayer << " on its place: ";
    cin >> input;

    if(input >= '1' && input <= '9')
    {
        if(input == '1'){//obavezno koristiti else if, bez njega dolazi do greske
            if(field[0][0] == '1'){
                field[0][0] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
        else if(input == '2'){
            if(field[0][2] == '2'){
                field[0][2] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
        else if(input == '3'){
            if(field[0][4] == '3'){
                field[0][4] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
        else if(input == '4'){
            if(field[2][0] == '4'){
                field[2][0] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
        else if(input == '5'){
            if(field[2][2] == '5'){
                field[2][2] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
        else if(input == '6'){
            if(field[2][4] == '6'){
                field[2][4] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
        else if(input == '7'){
            if(field[4][0] == '7'){
                field[4][0] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
        else if(input == '8'){
            if(field[4][2] == '8'){
                field[4][2] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
        else if(input == '9'){
            if(field[4][4] == '9'){
                field[4][4] = nextPlayer;
            } else {
                cout << "Field is already in use!" << endl;
                Input();
            }
        }
    }
    else
    {
        cout << "Field does not exist!" << endl;
        Input();
    }
}

void SwitchPlayer(){
    if(nextPlayer == 'X'){
        nextPlayer = 'O';
    } else {
        nextPlayer = 'X';
    }
}

char Win(){
    //horizontalno za X
    if(field[0][0] == 'X' && field[0][2] == 'X' && field[0][4] == 'X'){
        return 'X';
    }
    else if(field[2][0] == 'X' && field[2][2] == 'X' && field[2][4] == 'X'){
        return 'X';
    }
    else if(field[4][0] == 'X' && field[4][2] == 'X' && field[4][4] == 'X'){
        return 'X';
    }
    //vertikalno za X
    else if(field[0][0] == 'X' && field[2][0] == 'X' && field[4][0] == 'X'){
        return 'X';
    }
    else if(field[0][2] == 'X' && field[2][2] == 'X' && field[4][2] == 'X'){
        return 'X';
    }
    else if(field[0][4] == 'X' && field[2][4] == 'X' && field[4][4] == 'X'){
        return 'X';
    }
    //ukoso za X
    else if(field[0][0] == 'X' && field[2][2] == 'X' && field[4][4] == 'X'){
        return 'X';
    }
    else if(field[4][0] == 'X' && field[2][2] == 'X' && field[0][4] == 'X'){
        return 'X';
    }

    //horizontalno za O
    if(field[0][0] == 'O' && field[0][2] == 'O' && field[0][4] == 'O'){
        return 'O';
    }
    else if(field[2][0] == 'O' && field[2][2] == 'O' && field[2][4] == 'O'){
        return 'O';
    }
    else if(field[4][0] == 'O' && field[4][2] == 'O' && field[4][4] == 'O'){
        return 'O';
    }
    //vertikalno za O
    else if(field[0][0] == 'O' && field[2][0] == 'O' && field[4][0] == 'O'){
        return 'O';
    }
    else if(field[0][2] == 'O' && field[2][2] == 'O' && field[4][2] == 'O'){
        return 'O';
    }
    else if(field[0][4] == 'O' && field[2][4] == 'O' && field[4][4] == 'O'){
        return 'O';
    }
    //ukoso za O
    else if(field[0][0] == 'O' && field[2][2] == 'O' && field[4][4] == 'O'){
        return 'O';
    }
    else if(field[4][0] == 'O' && field[2][2] == 'O' && field[0][4] == 'O'){
        return 'O';
    }
    else
        return '/';//ako nije nista od gore navedenog
}

void StartUp(){
    cout << "Enter the number of wins to end game: ";
    cin >> scoreEnd;
}

int main()
{
    StartUp();
    Draw();
    while(!gameOver){
        Input();
        SwitchPlayer();
        Draw();
        counter++;
        if(Win() == 'X'){
            cout << "X is the winner" << endl;
			scoreX += 1;
			for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    field[i][j] = matrix[i][j];
                }
			}
            counter = 0;
            system("pause");//wait for any key to be pressed
            nextPlayer = 'X';
            Draw();
        }
        else if(Win() == 'O'){
            cout << "O is the winner" << endl;
            scoreO += 1;
			for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    field[i][j] = matrix[i][j];
                }
			}
            counter = 0;
            system("pause");
            nextPlayer = 'X';
            Draw();
        }
        else if(Win() == '/' && counter == 9){
            cout << "Its a draw" << endl;
			for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    field[i][j] = matrix[i][j];
                }
			}
            counter = 0;
            system("pause");
            nextPlayer = 'X';
            Draw();
        }

        if(scoreX == scoreEnd){
            gameOver = true;
            cout << "End of game." << endl;
            system("pause");
        }
        else if(scoreO == scoreEnd){
            gameOver = true;
            cout << "End of game." << endl;
            system("pause");
        }
    }
    return 0;
}
