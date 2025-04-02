#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


void displayBoard(char board[][3])
{
    cout << "      1  2  3 \n";
    for (int i = 0; i < 3;i++) {
        cout << "Row:" << i+1;
        for (int ii = 0; ii < 3;ii++) {
            cout << "|" << board[i][ii] << "|";
        }
        cout << "\n";
    }
}
bool boardCheck(char board[][3], bool &go, int &winner) {
    // test for horizontal wins
    for (int i = 0; i < 3;i++) {
        if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') {
            winner = 1;
            go = false;
        }
        else if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O') {
            winner = 2;
            go = false;
        }
    }
    // veritcal check
    for (int i = 0; i < 3;i++) {
        if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X') {
            winner = 1;
            go = false;
        }
        else if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O') {
            winner = 2;
            go = false;
        }
    }
    //diagonal check

        if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
            winner = 1;
            go = false;
        }
        else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
            winner = 2;
            go = false;
        }

        if (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X') {
            winner = 1;
            go = false;
        }
        else if (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O') {
            winner = 2;
            go = false;
        }

    int count = 0;
    if (winner == 0) {
        for (int i = 0; i < 3;i++) {
            for (int ii = 0; ii < 3;ii++) {
                if (board[i][ii] == 'X' || board[i][ii] == 'O') {
                    ++count;
                    if (count == 9) {
                        go = false;
                        winner = 0;
                    }
                }
            }
        }
    }

    return go;
}
int int_check() {
    string num;

    while (true) {
        getline(cin, num);

        if (num.length() == 1 && isdigit(num[0])) {
            int value = stoi(num); 
            
            if (value >= 1 && value <= 3) {
                return value;
            }
        }

        cout << "Error: Please enter a valid integer between 1 and 3.\n";
    }
}
bool place(char board[][3], int x, int y) {
    bool check = false;
    if (board[x][y] == ' ') {
        check = true;
    }
    return check;
}
void ticTacToe() {
    // make sure players cant place things in a area that already has a peice in it
    int winner = 0;
    char board[3][3];
    for (int i = 0; i < 3;i++) {
        for (int ii = 0; ii < 3;ii++) {
            board[i][ii] = ' ';
        }
    }
    displayBoard(board);
    bool go = true;
    while (go) {
        int x, y;
        while (true) {
            cout << "\nPlayer 1: enter what row and column you want to place your X in\nRow(1-3): ";
            x = int_check();
            x--;
            cout << "Col(1-3): ";
            y = int_check();
            y--;
            if (place(board, x, y)) {
                board[x][y] = 'X';
                break;
            }
            else {
                cout << "ERROR ALREADY TAKEN";
                continue;
            }
        }

        displayBoard(board);
        boardCheck(board, go, winner);
        if (!go) {
            break;
        }
        while (true) {
            cout << "\nPlayer 2: enter what row and column you want to place your O in\nRow(1-3): ";
            x = int_check();
            x--;
            cout << "Col(1-3): ";
            y = int_check();
            y--;
            if (place(board, x, y)) {
                board[x][y] = 'O';
                break;

            }
            else {
                cout << "ERROR ALREADY TAKEN";
                continue;
            }
        }
        displayBoard(board);
        boardCheck(board, go, winner);
    }
    if (winner == 1) {
        cout << "PLAYER 1 WIN!";
    }
    else if (winner == 2) {
        cout << "PLAYER 2 WIN!";

    }
    else {
        cout << "TIE GAME!";
    }
    cout << "\nThanks For Playing! ";
}


void HangmanGame(int game);

int main()
{
    cout << "Hello User! Welcome to the Mini-Game Terminal. Please choose which game you would like to play!" << endl;
    int choice;
    cin >> choice;

    switch (choice) {
        case(1):
            cout << "Transporting you to the Tic Tac Toe Minigame..." << endl;
            ticTacToe();
        default:
            cout << "DELETE LATER. More developing soon" << endl;
            
    return 0;

}

void HangmanGame(int game){


}
