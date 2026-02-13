#include <stdlib.h>
#include "raylib.h"
#include "game.h"
#include "colors.h"
#include "block.h"
#include <time.h>
#include <stdio.h>
#include "levels.h"
#include "sounds.h"
#include <string.h>

#define HEIGHT 620
#define WIDTH 500

#define BAG_SIZE 7

Block *currentBlock;
Block *nextBlock;
Block *holdBlock;
Block *ghostBlock;

Grid *grid;

int input;
int canHold;
int holding;
double lastUpdateTime = 0;
int score;
int gameOver;
int b2bTetris;
int level;
int totalLinesCleared;
Font font;
Music music;

BLOCK_TYPE bag[BAG_SIZE];

void updateGame();
void drawGame();
void initBlocks();
void shuffle();
void hold();
void endMove();
void updateScore(int linesCleared, int moveDownPoints);
Block *getNextBlock();
void resetGame();
void changeGhostBlock(BLOCK_TYPE t);
int handleInput();

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
    InitAudioDevice();
    SetTargetFPS(60);
    loadSounds();
    font = LoadFont("Assets/Font/monogram.ttf");
    music = LoadMusicStream("Assets/Sound/Music.wav");
    music.looping = true;
    SetMusicVolume(music, 0.5f);
    PlayMusicStream(music);
    srand(time(NULL));
    initBlocks();
    shuffle();
    currentBlock = getNextBlock();
    nextBlock = getNextBlock();
    ghostBlock = createBlock(getBlockType(currentBlock));
    holdBlock = NULL;
    grid = createGrid();
    score = 0;
    gameOver = 0;
    holding = 0;
    canHold = 1;
    b2bTetris = 0;
    level = 1;
    totalLinesCleared = 0;
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
    destroyBlock(holdBlock);
    destroyBlock(nextBlock);
    destroyBlock(currentBlock);
    destroyBlock(ghostBlock);
    destroyGrid(grid);
    unloadSounds();
    UnloadFont(font);
    UnloadMusicStream(music);
    CloseWindow();
}

void updateGame()
{
    UpdateMusicStream(music);

    input = handleInput();
    resetGhostBlockRow(ghostBlock, currentBlock);
    int prevLevel = level;
    level = calcCurrentLevel(totalLinesCleared);
    if (level < prevLevel) PlaySound(levelUpS);
    double intervel = getIntervel(level);
    if (!gameOver)
    {

        if (eventTriggered(intervel))
        {
            if (checkValidMove(currentBlock, DOWN, grid))
            {
                move(currentBlock, DOWN);
                PlaySound(movePieceS);
            }
            else 
            {
                endMove();
            }
        }
        
        switch (input)
        {
            case KEY_UP:
                if(checkValidRotation(currentBlock, grid))
                {
                    rotate(currentBlock);
                    PlaySound(rotatePieceS);
                    rotate(ghostBlock);
                }
                break;
            case KEY_DOWN:
                if (checkValidMove(currentBlock, DOWN, grid))
                {
                    move(currentBlock, DOWN);
                    PlaySound(movePieceS);
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
                    PlaySound(movePieceS);
                    move(ghostBlock, RIGHT);
                }
                break;
            case KEY_LEFT:
                if (checkValidMove(currentBlock, LEFT, grid))
                {
                    move(currentBlock, LEFT);
                    PlaySound(movePieceS);
                    move(ghostBlock, LEFT);
                }
                break; 
            case KEY_SPACE:
                updateScore(0, hardDrop(currentBlock, grid) * 2);
                endMove();
                break;
            case KEY_C:
                if(canHold) hold();
                break;
        }

        hardDrop(ghostBlock, grid);
    }
    else 
    {
        if (input == KEY_ENTER)
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
    drawGhostBlock(ghostBlock, 11, 11);

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
        bag[i] = (BLOCK_TYPE)(i + 1);
    }
}

void shuffle()
{
    for (int i = BAG_SIZE - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        BLOCK_TYPE temp = bag[i];
        bag[i] = bag[j];
        bag[j] = temp;
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
    changeGhostBlock(getBlockType(currentBlock));
    holding = 1;
}

Block *getNextBlock()
{
    for (int i = 0; i < BAG_SIZE; i++)
    {
        if (bag[i] == 0) continue;
        BLOCK_TYPE t = bag[i];
        bag[i] = 0;
        return createBlock(t);
    }
    initBlocks();
    shuffle();
    return getNextBlock();
}

void endMove()
{
    lockBlock(currentBlock, grid);
    PlaySound(pieceLandedS);
    destroyBlock(currentBlock);
    currentBlock = nextBlock;
    changeGhostBlock(getBlockType(currentBlock));
    if (!checkValidMove(currentBlock, 0, grid))
    {
        gameOver = 1;
        PlaySound(gameOverS);
    }
    nextBlock = getNextBlock();
    int rowsCleared = clearFullRows(grid);
    updateScore(rowsCleared, 0);
    totalLinesCleared += rowsCleared;
    canHold = 1;
}

void updateScore(int linesCleared, int moveDownPoints)
{
    int multiplier = 1.5;
    switch (linesCleared)
    {
        case 1:
            score += 100 * level;
            b2bTetris = 0;
            PlaySound(lineClearS);
            break;
        case 2:
            score += 300 * level;
            b2bTetris = 0;
            PlaySound(lineClearS);
            break;
        case 3:
            score += 500 * level;
            b2bTetris = 0;
            PlaySound(lineClearS);
            break;
        case 4:
            if (b2bTetris)
            {
                score += (800 * level) * multiplier;
            }
            else
            {
                score += 800 * level;
                b2bTetris = 1;
            }
            PlaySound(tetrisS);
            break;
    }
    score += moveDownPoints;
}

void resetGame()
{
    destroyBlock(holdBlock);
    destroyBlock(nextBlock);
    destroyBlock(ghostBlock);
    destroyBlock(currentBlock);
    destroyGrid(grid);
    initBlocks();
    shuffle();
    currentBlock = getNextBlock();
    ghostBlock = createBlock(getBlockType(currentBlock));
    nextBlock = getNextBlock();
    holdBlock = NULL;
    grid = createGrid();
    score = 0;
    holding = 0;
    canHold = 1;
    gameOver = 0;
    b2bTetris = 0;
    level = 1;
    totalLinesCleared = 0;
}

void changeGhostBlock(BLOCK_TYPE t)
{
    destroyBlock(ghostBlock);
    ghostBlock = createBlock(t);
}

int handleInput()
{
    if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) return KEY_UP;
    if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) return KEY_DOWN;
    if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) return KEY_LEFT;
    if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) return KEY_RIGHT;
    if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) return KEY_C;
    if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) return KEY_SPACE;
    if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)) return KEY_ENTER;

    int keyPressed = GetKeyPressed();
    return keyPressed;
}

typedef struct Move {
    int colOffset, numRotations;
    float score;
} Move;

Move findBestMove(Block *block, Grid *copyGrid, int rotation)
{
    
}

void aiPlay(BLOCK_TYPE bt, Grid *g)
{
    Grid *copy = malloc(sizeof(*g));
    memcpy(copy, g, sizeof(copy));
    Block *base = createBlock(bt);

    Move bestMove = {0, 0, -1e9f};

    for (int r = 0; r < 4; r++)
    {
        Block *b = cloneBlock(base);
        for (int i = 0; i < r; i++) rotate(b);

        Move m = findBestMove(b, copy, r);
        if (m.score > bestMove.score) bestMove = m;

        free(b);
    }

    for (int i = 0; i < bestMove.numRotations; i++)
        rotate(currentBlock);

    if (bestMove.colOffset > 0)
    {
        for (int i = 0; i < bestMove.colOffset; i++) move(currentBlock, RIGHT);
    }
    else
    {
        for (int i = 0; i < -bestMove.colOffset; i++) move(currentBlock, LEFT);
    }

    updateScore(0, hardDrop(currentBlock, g) * 2);
    endMove();

    free(base);
    free(copy);
}