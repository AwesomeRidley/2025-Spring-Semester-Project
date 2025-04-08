#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <random>

using namespace std;


void displayBoard(char board[][3])
{
    cout << "      1  2  3 \n";
    for (int i = 0; i < 3;i++) {
        cout << "Row:" << i + 1;
        for (int ii = 0; ii < 3;ii++) {
            cout << "|" << board[i][ii] << "|";
        }
        cout << "\n";
    }
}
bool boardCheck(char board[][3], bool& go, int& winner) {
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
        //Added this input stream cleaner I found online. Its said to help with a bug that makes the error message appear first.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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


void HangmanGame();
void display_hangman(int& man);
bool guessing_word(char ptr_to_guess[], char ptr_to_word[], char ptr_to_already_guessed[], int size_of_word, int& man, int& tries);

int main()
{
    cout << "Hello User! Welcome to the Mini-Game Terminal. Please choose which game you would like to play!" << endl;
    int choice;
    cin >> choice;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    do
    {
        switch (choice)
        {
        case(1):
            cout << "\nTransporting you to the Tic Tac Toe Minigame..." << endl;
            ticTacToe();
            break;
        case(2):
            cout << "\nTransporting you to the Hangman Minigame..." << endl;
            HangmanGame();
            break;
        default:
            cout << "\nThat's all! Thanks for Playing!" << endl;
        }

        cout << "That was fun! What would you like to play next? (1 - 3): ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice != 0);
    return 0;

}

void HangmanGame() 
{
    cout << "\nWelcome to hangman user. Guess the word below and save the man" << endl;
    int tries = 0;
    bool wish_to_play = true;
    bool win_or_loss = false;

    do //Only 12 tries. Then it's Gameover.
    {
        int man = 0;
        srand(static_cast<unsigned int>(time(0))); //Sets up the random integer so that the word picked will be random.//
        int random_word = rand() % 100 + 1;

        string word; //Opens the file and sets up the variable holding the random word.//
        ifstream File;
        File.open("Random Hangman Words.txt");

        if (File.is_open())
        {
            for (int i = 1; i <= random_word; ++i)
            {
                getline(File, word);
            }
        }
        else
        {
            cout << "ERROR: File Failed To Open." << endl;
        }

        size_t size_of_word = word.length(); //Gets the size of the randomly selected word.//
        char* ptr_to_word = new char[size_of_word]; //Creates two new arrays. One to split the word into characters, and another to be the guessing array.
        char* ptr_to_guess = new char[size_of_word];
        char* ptr_to_already_guessed = new char[27];

        for (int i = 0; i < size_of_word; ++i)
        {
            ptr_to_word[i] = word[i]; //Assigns the characters to each array//
            ptr_to_guess[i] = '-';
        }

        while (wish_to_play)
        {
            win_or_loss = guessing_word(ptr_to_guess, ptr_to_word, ptr_to_already_guessed, size_of_word, man, tries);

            if (win_or_loss)
            {
                wish_to_play = false;
            }
            else if (man == 12)
            {
                cout << "\n---------------" << endl;
                cout << "       |      |" << endl;
                cout << "      ---     |" << endl;
                cout << "    | X X |   |" << endl;
                cout << "      ---     |" << endl;
                cout << "       |      |" << endl;
                cout << "     / | \\    |" << endl;
                cout << "    /  |  \\   |" << endl;
                cout << "       |      |" << endl;
                cout << "       -      |" << endl;
                cout << "     /   \\    |" << endl;
                cout << "    /     \\   |" << endl;
                cout << "           -------" << endl;
                cout << "Unfortunate. You lost and the man was hanged" << endl;
                cout << "The word was " << word << endl;
                break;
            }
        }

        delete[] ptr_to_word;
        delete[] ptr_to_guess;
        delete[] ptr_to_already_guessed;

        cout << endl << endl << "Would you like to try again? (Enter 1 or 0): ";
        cin >> wish_to_play;

    } while (wish_to_play);
}

bool guessing_word(char ptr_to_guess[], char ptr_to_word[], char ptr_to_already_guessed[], int size_of_word, int& man, int& tries) //This function will display what letters have been guessed correctly yet and what remains unknown.
{
    display_hangman(man); //Displays the man hanging//

    int tally = 0;
    for (int i = 0; i < size_of_word; i++) //Displays the blocked word. Will unlock character by character if the user guesses correctly//
    {
        cout << ptr_to_guess[i];

        if (ptr_to_guess[i] == '-')
        {
            tally++;
        }
    }

    if (tally > 0)
    {
        cout << endl << endl << "Enter your letter: ";
        char guessed_letter;
        cin >> guessed_letter;

        bool guessed_a_word = false;
        bool already_guessed = false;

        for (int j = 0; j < tries; j++)
        {
            if (ptr_to_already_guessed[j] == guessed_letter)
            {
                ptr_to_already_guessed[j] = guessed_letter;
                cout << "This letter was already used. Try Again.";
                return false;
            }
        }

        for (int i = 0; i < size_of_word; i++)
        {
            if (ptr_to_word[i] == guessed_letter)
            {
                ptr_to_guess[i] = guessed_letter;
                guessed_a_word = true;
            }
        }

        if (tries < 26)
        {
            ptr_to_already_guessed[tries] = guessed_letter;
        }
        if (guessed_a_word == false)
        {
            man++;
        }
        tries++;
    }
    else
    {
        cout << "\n\nCongrats! You guessed the word and saved the man!" << endl << endl;
        cout << "     \"Yay!\"        " << endl;
        cout << "      ---     " << endl;
        cout << "    | ^ ^ |   " << endl;
        cout << "      ---     " << endl;
        cout << "    \\  |  /    " << endl;
        cout << "     \\ | /    " << endl;
        cout << "       |     " << endl;
        cout << "       |      " << endl;
        cout << "       -      " << endl;
        cout << "     /   \\    " << endl;
        cout << "    /     \\   " << endl;
        return true;
    }
    return false;
}

void display_hangman(int& man) //Outputs the Hanging man//
{
    if (man == 0)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 1)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 2)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 3)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 4)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 5)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "       |      |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 6)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "       |      |" << endl;
        cout << "     / | \\    |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 7)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "       |      |" << endl;
        cout << "     / | \\    |" << endl;
        cout << "    /  |  \\   |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 8)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "       |      |" << endl;
        cout << "     / | \\    |" << endl;
        cout << "    /  |  \\   |" << endl;
        cout << "       |      |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 9)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "       |      |" << endl;
        cout << "     / | \\    |" << endl;
        cout << "    /  |  \\   |" << endl;
        cout << "       |      |" << endl;
        cout << "       -      |" << endl;
        cout << "              |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 10)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "       |      |" << endl;
        cout << "     / | \\    |" << endl;
        cout << "    /  |  \\   |" << endl;
        cout << "       |      |" << endl;
        cout << "       -      |" << endl;
        cout << "     /   \\    |" << endl;
        cout << "              |" << endl;
        cout << "           -------" << endl;
    }
    else if (man == 11)
    {
        cout << "---------------" << endl;
        cout << "       |      |" << endl;
        cout << "      ---     |" << endl;
        cout << "    | O O |   |" << endl;
        cout << "      ---     |" << endl;
        cout << "       |      |" << endl;
        cout << "     / | \\    |" << endl;
        cout << "    /  |  \\   |" << endl;
        cout << "       |      |" << endl;
        cout << "       -      |" << endl;
        cout << "     /   \\    |" << endl;
        cout << "    /     \\   |" << endl;
        cout << "           -------" << endl;
    }
}
