#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>



// Y --> height
// X --> width



// The dimensions of the map

const int height = 20;

const int width = 40;



// The map --> 2d array

char map[height][width];



// The dimensions of the second map

int map2[height][width] = { 0 };



// Starting position of the snake's head

int headLocY = height / 2;

int headLocX = width / 2;



// Position of the fruit

int fruitLocY;

int fruitLocX;



// String indicating snake direction

std::string direction = "up";



// Boolean for program loop

bool running = true;



// Boolean for fruits

bool fruitExists = false;

bool CreateFruit = true;



// Size of snake

int size = 4;



// Number to be deleted from grid

int numberDelete;



// Counter

int counter = 1;



// Sleep time

int sleepTime;



// Bool for introduction
bool intro = true;



// Bool for playing again
bool replay;




void gotoxy(int a, int b) {
    COORD pos = { a,b };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


// Function that initialises map
void InitMap() {

    // Fills every character of the map with a space
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = ' ';
        }
    }

    // Create left and right walls with '#'
    for (int i = 0; i < height; i++) {
        map[i][0] = '#';
        map[i][39] = '#';
    }

    // Create upper and lower walls with '#'
    for (int i = 0; i < width; i++) {
        map[0][i] = '#';
        map[19][i] = '#';
    }

}



// Function that detects change of direction with keyboard (W,A,S,D)
void ChangeDirection(char key) {
    switch (key) {
    case 'w': {
        if (direction != "down") {
            direction = "up";
            break;
        }
    }
    case 's': {
        if (direction != "up") {
            direction = "down";
            break;
        }
    }
    case 'a': {
        if (direction != "right") {
            direction = "left";
            break;
        }
    }
    case 'd': {
        if (direction != "left") {
            direction = "right";
            break;
        }
    }

    default: {
        break;
    }
    }
}



// Function that moves snake in the wanted direction
void MoveSnake() {

    if (direction == "up")
    {
        headLocY--;
        map[headLocY][headLocX] = 'O';
    }
    else if (direction == "down")
    {
        headLocY++;
        map[headLocY][headLocX] = 'O';
    }
    else if (direction == "right")
    {
        headLocX++;
        map[headLocY][headLocX] = 'O';
    }
    else if (direction == "left")
    {
        headLocX--;
        map[headLocY][headLocX] = 'O';
    }
    map2[headLocY][headLocX] = counter;

}



// Erases snake's tail
void EraseSnake() {
    if (size < counter) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (map2[i][j] == counter - size) {
                    map[i][j] = ' ';
                }
            }
        }
    }
    counter++;
}



// Generates fruit
void GenerateFood() {

    // If snake eats fruit, create a new one
    if (fruitLocX == headLocX && fruitLocY == headLocY) {
        CreateFruit = true;
        size++;
    }

    // Keep looping until a valid place is found
    while (CreateFruit) {
        fruitLocY = rand() % 20;
        fruitLocX = rand() % 40;

        // Check if place is empty
        if (map[fruitLocY][fruitLocX] == ' ') {
            map[fruitLocY][fruitLocX] = '$';
            CreateFruit = false;
        }
    }
}





// Function that prints map on the console
void PrintMap() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << map[i][j];
        }
        std::cout << '\n';
    }
    // Display score and size
    std::cout << '\n' << '\t' << "Score : " << size - 4 << '\t' << "Size : " << size << '\t';
}


// Checks if you lost
void Lose() {
    // Checks if it finds snake's head in the walls
    for (int i = 0; i < height; i++) {
        if (map[i][0] == 'O' || map[i][39] == 'O') {
            running = false;
        }
    }

    // Checks if it finds snake's head in the walls
    for (int i = 0; i < width; i++) {
        if (map[0][i] == 'O' || map[19][i] == 'O') {
            running = false;
        }
    }
}



// Hides cursor
void HideCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}



int main() {

    HideCursor();
    // Allows random number to be created
    srand(time(0));
    InitMap();

    while (running) {

        // Detects key presses
        if (_kbhit()) {
            ChangeDirection(_getch());
        }

        GenerateFood();
        MoveSnake();
        EraseSnake();
        Lose();

        // Clears screen
        gotoxy(0, 0);
        PrintMap();
        Sleep(500);
    }
    return 0;
}