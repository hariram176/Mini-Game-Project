#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Game area
const int WIDTH = 40;
const int HEIGHT = 20;

// Snake variables
int x, y;
int fruitX, fruitY;
int score;

int tailX[100];
int tailY[100];
int tailLength;

// Game states
enum Direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

Direction dir;

// Setup the game
void setup() {
    dir = STOP;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    srand(time(0));

    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;

    score = 0;
    tailLength = 0;
}

// Display the game board
void draw() {

    system("cls");

    // Top border
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";

    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {

        for (int j = 0; j < WIDTH; j++) {

            // Left border
            if (j == 0)
                cout << "#";

            // Snake head
            if (i == y && j == x)
                cout << "O";

            // Fruit
            else if (i == fruitY && j == fruitX)
                cout << "*";

            else {

                bool printTail = false;

                for (int k = 0; k < tailLength; k++) {

                    if (tailX[k] == j &&
                        tailY[k] == i) {

                        cout << "o";
                        printTail = true;
                        break;
                    }
                }

                if (!printTail)
                    cout << " ";
            }

            // Right border
            if (j == WIDTH - 1)
                cout << "#";
        }

        cout << endl;
    }

    // Bottom border
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";

    cout << endl;

    cout << "Score: " << score << endl;
    cout << "Controls: W = Up, S = Down, A = Left, D = Right";
    cout << "\nPress X to exit the game.\n";
}

// Get keyboard input
void input() {

    if (_kbhit()) {

        switch (_getch()) {

            case 'a':
            case 'A':
                if (dir != RIGHT)
                    dir = LEFT;
                break;

            case 'd':
            case 'D':
                if (dir != LEFT)
                    dir = RIGHT;
                break;

            case 'w':
            case 'W':
                if (dir != DOWN)
                    dir = UP;
                break;

            case 's':
            case 'S':
                if (dir != UP)
                    dir = DOWN;
                break;

            case 'x':
            case 'X':
                exit(0);
        }
    }
}

// Game logic
bool logic() {

    // Move the tail
    int previousX = tailX[0];
    int previousY = tailY[0];

    int previous2X;
    int previous2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {

        previous2X = tailX[i];
        previous2Y = tailY[i];

        tailX[i] = previousX;
        tailY[i] = previousY;

        previousX = previous2X;
        previousY = previous2Y;
    }

    // Move the snake head
    switch (dir) {

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

        case STOP:
            break;
    }

    // Collision with walls
    if (x < 0 || x >= WIDTH ||
        y < 0 || y >= HEIGHT) {

        return false;
    }

    // Collision with tail
    for (int i = 0; i < tailLength; i++) {

        if (tailX[i] == x &&
            tailY[i] == y) {

            return false;
        }
    }

    // Snake eats fruit
    if (x == fruitX && y == fruitY) {

        score += 10;

        if (tailLength < 99)
            tailLength++;

        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }

    return true;
}

// Main function
int main() {

    setup();

    bool gameOver = false;

    while (!gameOver) {

        draw();

        input();

        gameOver = !logic();

        Sleep(100);
    }

    system("cls");

    cout << "\n====================================\n";
    cout << "             GAME OVER!\n";
    cout << "====================================\n";

    cout << "\nFinal Score: " << score << endl;

    char choice;

    cout << "\nDo you want to play again? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {

        main();

    } else {

        cout << "\nThank you for playing Snake Game!\n";
    }

    return 0;
}