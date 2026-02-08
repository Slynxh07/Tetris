#include <stdlib.h>
#include "raylib.h"
#include "game.h"
#include "colors.h"
#include "block.h"
#include <time.h>
#include <stdio.h>

#define HEIGHT 620
#define WIDTH 500

#define BAG_SIZE 7

Block *currentBlock;
Block *nextBlock;
Block *holdBlock;

Grid *grid;

int keyPressed;
int canHold;
int holding;
double lastUpdateTime = 0;
int score;
int gameOver;
Font font;

Block *bag[BAG_SIZE];

void updateGame();
void drawGame();
void initBlocks();
void shuffle();
void hold();
void endMove();
void updateScore(int linesCleared, int moveDownPoints);
Block *getNextBlock();
void resetGame();

int eventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return 1;
	}
	return 0;
}

void initGame()
{
    InitWindow(WIDTH, HEIGHT, "Teris");
    SetTargetFPS(60);
    font = LoadFont("Assets/Font/monogram.ttf");
    srand(time(NULL));
    initBlocks();
    shuffle();
    currentBlock = getNextBlock();
    nextBlock = getNextBlock();
    holdBlock = NULL;
    grid = createGrid();
    score = 0;
    gameOver = 0;
    holding = 0;
    canHold = 1;
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
    for (int i = 0; i < BAG_SIZE; i++)
    {
        destroyBlock(bag[i]);
    }
    destroyBlock(holdBlock);
    destroyBlock(nextBlock);
    destroyBlock(currentBlock);
    destroyGrid(grid);
}

void updateGame()
{
    keyPressed = GetKeyPressed();

    if (!gameOver)
    {

        if (eventTriggered(1))
        {
            if (checkValidMove(currentBlock, DOWN, grid))
            {
                move(currentBlock, DOWN);
            }
            else 
            {
                endMove();
            }
        }
        
        switch (keyPressed)
        {
            case KEY_UP:
                if(checkValidRotation(currentBlock, grid))
                {
                    rotate(currentBlock);
                }
                break;
            case KEY_DOWN:
                if (checkValidMove(currentBlock, DOWN, grid))
                {
                    move(currentBlock, DOWN);
                    updateScore(0, 1);
                }
                else 
                {
                    endMove();
                }
                break;
            case KEY_RIGHT:
                if (checkValidMove(currentBlock, RIGHT, grid))
                {
                    move(currentBlock, RIGHT);
                }
                break;
            case KEY_LEFT:
                if (checkValidMove(currentBlock, LEFT, grid))
                {
                    move(currentBlock, LEFT);   
                }
                break; 
            case KEY_SPACE:
                if(canHold) hold();
                break;
        }
    }
    else 
    {
        if (keyPressed == KEY_ENTER)
        {
            resetGame();
        }
    }
}

void drawGame()
{
    BeginDrawing();

    ClearBackground(backGround);

    if (gameOver)
	{
		DrawTextEx(font, "GAME OVER", (Vector2) { 320, 570 }, 38, 2, WHITE);
	}

    DrawTextEx(font, "Score", (Vector2) { 365, 15 }, 38, 2, WHITE);
    DrawTextEx(font, "Next", (Vector2) { 370, 125 }, 38, 2, WHITE);
    DrawTextEx(font, "Held", (Vector2) { 370, 345 }, 38, 2, WHITE);
    
    DrawRectangleRounded((Rectangle){ 320, 55, 170, 60 }, 0.3, 6, lightBlue);

    char scoreText[10];
    snprintf(scoreText, sizeof(scoreText), "%d", score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, scoreText, (Vector2) { 320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

    DrawRectangleRounded((Rectangle){ 320, 165, 170, 180 }, 0.3, 6, lightBlue);
    DrawRectangleRounded((Rectangle){ 320, 385, 170, 180 }, 0.3, 6, lightBlue);

    drawTGrid(grid);
    drawBlock(currentBlock, 11, 11);

    switch (getBlockType(nextBlock))
	{
        case HERO:
            drawBlock(nextBlock, 255, 240);
            break;
        case SMASHBOY:
            drawBlock(nextBlock, 255, 230);
            break;
        default:
            drawBlock(nextBlock, 270, 220);
            break;
	}

    if (holding)
	{
		switch (getBlockType(holdBlock))
		{
            case HERO:
                drawBlock(holdBlock, 255, 460);
                break;
            case SMASHBOY:
                drawBlock(holdBlock, 255, 450);
                break;
            default:
                drawBlock(holdBlock, 270, 440);
                break;
		}
    }
    EndDrawing();
}

void initBlocks()
{
    for (int i = 0; i < BAG_SIZE; i++)
    {
        bag[i] = createBlock((BLOCK_TYPE)(i + 1));
    }
}

void shuffle()
{
    for (int i = BAG_SIZE - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        SWAP_BLOCK_PTR(bag[i], bag[j]);
    }
}

void hold()
{
    canHold = 0;
    resetBlock(currentBlock);
    if (holding)
    {
        SWAP_BLOCK_PTR(holdBlock, currentBlock);
    }
    else
    {
        holdBlock = currentBlock;
        currentBlock = nextBlock;
        nextBlock = getNextBlock();
    }
    holding = 1;
}

Block *getNextBlock()
{
    Block *retBlock;
    for (int i = 0; i < BAG_SIZE; i++)
    {
        if (bag[i] == NULL) continue;
        retBlock = bag[i]; 
        bag[i] = NULL;   
        return retBlock;
    }
    initBlocks();
    shuffle();
    return getNextBlock();
}

void endMove()
{
    lockBlock(currentBlock, grid);
    destroyBlock(currentBlock);
    currentBlock = nextBlock;
    if (!checkValidMove(currentBlock, 0, grid))
    {
        gameOver = 1;
    }
    nextBlock = getNextBlock();
    int rowsCleared = clearFullRows(grid);
    updateScore(rowsCleared, 0);
    canHold = 1;
}

void updateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	case 4:
		score += 1000;
		break;
	default:
		break;
	}
	score += moveDownPoints;
}

void resetGame()
{
    closeGame();
    initBlocks();
    shuffle();
    currentBlock = getNextBlock();
    nextBlock = getNextBlock();
    holdBlock = NULL;
    grid = createGrid();
    score = 0;
    holding = 0;
    canHold = 1;
    gameOver = 0;
}