#include <iostream>
#include <cstdlib>
using namespace std;

// Display the game board
void displayBoard(char board[]) {
    cout << "\n";
    cout << "     |     |     \n";
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";
    cout << "_____|_____|_____\n";

    cout << "     |     |     \n";
    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";
    cout << "_____|_____|_____\n";

    cout << "     |     |     \n";
    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
    cout << "     |     |     \n";
}

// Check whether a player has won
bool checkWin(char board[], char player) {

    // Rows
    if (board[0] == player &&
        board[1] == player &&
        board[2] == player)
        return true;

    if (board[3] == player &&
        board[4] == player &&
        board[5] == player)
        return true;

    if (board[6] == player &&
        board[7] == player &&
        board[8] == player)
        return true;

    // Columns
    if (board[0] == player &&
        board[3] == player &&
        board[6] == player)
        return true;

    if (board[1] == player &&
        board[4] == player &&
        board[7] == player)
        return true;

    if (board[2] == player &&
        board[5] == player &&
        board[8] == player)
        return true;

    // Diagonals
    if (board[0] == player &&
        board[4] == player &&
        board[8] == player)
        return true;

    if (board[2] == player &&
        board[4] == player &&
        board[6] == player)
        return true;

    return false;
}

// Check whether the board is full
bool checkDraw(char board[]) {

    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return false;
        }
    }

    return true;
}

// Play one game
void playGame() {

    char board[9] = {
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9'
    };

    char currentPlayer = 'X';
    int position;

    cout << "\n====================================\n";
    cout << "          TIC TAC TOE GAME\n";
    cout << "====================================\n";

    cout << "\nPlayer 1: X";
    cout << "\nPlayer 2: O\n";

    while (true) {

        displayBoard(board);

        cout << "\nPlayer " << currentPlayer;
        cout << ", enter position (1-9): ";

        cin >> position;

        // Validate input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        // Validate range
        if (position < 1 || position > 9) {
            cout << "\nInvalid position! Choose between 1 and 9.\n";
            continue;
        }

        // Check whether position is already occupied
        if (board[position - 1] == 'X' ||
            board[position - 1] == 'O') {

            cout << "\nPosition already occupied! Choose another position.\n";
            continue;
        }

        // Place player's symbol
        board[position - 1] = currentPlayer;

        // Check winner
        if (checkWin(board, currentPlayer)) {

            displayBoard(board);

            cout << "\n====================================\n";
            cout << "       PLAYER " << currentPlayer << " WINS!\n";
            cout << "====================================\n";

            break;
        }

        // Check draw
        if (checkDraw(board)) {

            displayBoard(board);

            cout << "\n====================================\n";
            cout << "             GAME DRAW!\n";
            cout << "====================================\n";

            break;
        }

        // Change player
        if (currentPlayer == 'X')
            currentPlayer = 'O';
        else
            currentPlayer = 'X';
    }
}

// Main function
int main() {

    char playAgain;

    do {

        playGame();

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;

        system("cls");

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "\n====================================\n";
    cout << "     Thank you for playing!\n";
    cout << "====================================\n";

    return 0;
}