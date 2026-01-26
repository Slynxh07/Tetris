#include "raylib.h"
#include "game.h"
#include "colors.h"

#define HEIGHT 900
#define WIDTH 600

void updateGame();
void drawGame();

void initGame()
{
    InitWindow(WIDTH, HEIGHT, "Teris");
}

void runGame()
{
    while (!WindowShouldClose())
    {
        updateGame();
        drawGame();
    }
}

void closeGame()
{
    //free memory
}

void updateGame()
{

}

void drawGame()
{
    BeginDrawing();

    ClearBackground(backGround);

    EndDrawing();
}