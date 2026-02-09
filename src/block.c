#include "block.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

#define NUM_CELLS 4
#define CELL_SIZE 30

static const Position ORANGE_RICKY_CELLS[NUM_CELLS][NUM_CELLS] = {
    { {0,2}, {1,0}, {1,1}, {1,2} },
    { {0,1}, {1,1}, {2,1}, {2,2} },
    { {1,0}, {1,1}, {1,2}, {2,0} },
    { {0,0}, {0,1}, {1,1}, {2,1} }
};

static const Position BLUE_RICKY_CELLS[NUM_CELLS][NUM_CELLS] = {
    { {0,0}, {1,0}, {1,1}, {1,2} },
    { {0,1}, {0,2}, {1,1}, {2,1} },
    { {1,0}, {1,1}, {1,2}, {2,2} },
    { {0,1}, {1,1}, {2,0}, {2,1} }
};

static const Position CLEVELAND_Z_CELLS[NUM_CELLS][NUM_CELLS] = {
    { {0,0}, {0,1}, {1,1}, {1,2} },
    { {0,2}, {1,1}, {1,2}, {2,1} },
    { {1,0}, {1,1}, {2,1}, {2,2} },
    { {0,1}, {1,0}, {1,1}, {2,0} }
};

static const Position RHODE_ISLAND_Z_CELLS[NUM_CELLS][NUM_CELLS] = {
    { {0,1}, {0,2}, {1,0}, {1,1} },
    { {0,1}, {1,1}, {1,2}, {2,2} },
    { {1,1}, {1,2}, {2,0}, {2,1} },
    { {0,0}, {1,0}, {1,1}, {2,1} }
};

static const Position HERO_CELLS[NUM_CELLS][NUM_CELLS] = {
    { {1,0}, {1,1}, {1,2}, {1,3} },
    { {0,2}, {1,2}, {2,2}, {3,2} },
    { {2,0}, {2,1}, {2,2}, {2,3} },
    { {0,1}, {1,1}, {2,1}, {3,1} }
};

static const Position TEEWEE_CELLS[NUM_CELLS][NUM_CELLS] = {
    { {0,1}, {1,0}, {1,1}, {1,2} },
    { {0,1}, {1,1}, {1,2}, {2,1} },
    { {1,0}, {1,1}, {1,2}, {2,1} },
    { {0,1}, {1,0}, {1,1}, {2,1} }
};

static const Position SMASHBOY_CELLS[NUM_CELLS][NUM_CELLS] = {
    { {0,0}, {0,1}, {1,0}, {1,1} },
    { {0,0}, {0,1}, {1,0}, {1,1} },
    { {0,0}, {0,1}, {1,0}, {1,1} },
    { {0,0}, {0,1}, {1,0}, {1,1} }
};

typedef struct Block {
    Position cells[NUM_CELLS][NUM_CELLS];
    BLOCK_TYPE blockType;
    int rowOffset;
    int colOffset;
    int rotateState;
} Block;

void getCellPositions(const Block *b, Position out[NUM_CELLS]);

Block *createBlock(BLOCK_TYPE blockType)
{
    Block *b = malloc(sizeof(Block));
    b->blockType = blockType;
    switch (blockType)
    {
    case ORANGE_RICKY:
        memcpy(b->cells, ORANGE_RICKY_CELLS, sizeof(b->cells));
        b->colOffset = 3;
        b->rowOffset = 0;
        break;
    case BLUE_RICKY:
        memcpy(b->cells, BLUE_RICKY_CELLS, sizeof(b->cells));
        b->colOffset = 3;
        b->rowOffset = 0;
        break;
    case CLEVELAND_Z:
        memcpy(b->cells, CLEVELAND_Z_CELLS, sizeof(b->cells));
        b->colOffset = 3;
        b->rowOffset = 0;
        break;
    case RHODE_ISLAND_Z:
        memcpy(b->cells, RHODE_ISLAND_Z_CELLS, sizeof(b->cells));
        b->colOffset = 3;
        b->rowOffset = 0;
        break;
    case HERO:
        memcpy(b->cells, HERO_CELLS, sizeof(b->cells));
        b->colOffset = 3;
        b->rowOffset = -1;
        break;
    case TEEWEE:
        memcpy(b->cells, TEEWEE_CELLS, sizeof(b->cells));
        b->colOffset = 3;
        b->rowOffset = 0;
        break;
    case SMASHBOY:
        memcpy(b->cells, SMASHBOY_CELLS, sizeof(b->cells));
        b->colOffset = 4;
        b->rowOffset = 0;
        break;
    default:
        printf("Error creating block...");
        exit(-1);
        break;
    }
    b->rotateState = 0;
    return b;
}

BLOCK_TYPE getBlockType(const Block *b)
{
    return b->blockType;
}

void destroyBlock(Block *b)
{
    if (b != NULL) free(b);
}

void rotate(Block *b)
{
    b->rotateState++;
    if (b->rotateState >= 4) b->rotateState = 0;
}

void move(Block *b, Direction dir)
{
    switch (dir)
    {
        case DOWN:
            b->rowOffset++;
            break;
        case LEFT:
            b->colOffset--;
            break;
        case RIGHT:
            b->colOffset++;
            break;
        default:
            printf("Invlaid input, don't know how you got here...");
            exit(-1);
            break;
    }
}

int hardDrop(Block *b, Grid *g)
{
    int rowsDropped = 0;
    while (checkValidMove(b, DOWN, g))
    {
        move(b, DOWN);
        rowsDropped++;
    }
    return rowsDropped;
}

void resetGhostBlockRow(Block *targetB, Block *fromB)
{
    targetB->rowOffset = fromB->rowOffset;
}

void drawBlock(const Block *b, int xOffset, int yOffset)
{
    Position newPos[NUM_CELLS];
    getCellPositions(b, newPos);
    for (int i = 0; i < NUM_CELLS; i++)
    {
        DrawRectangle(newPos[i].col * CELL_SIZE + xOffset, newPos[i].row * CELL_SIZE + yOffset, CELL_SIZE - 1, CELL_SIZE - 1, brickColors[b->blockType]);
    }
}

void drawGhostBlock(const Block *b, int xOffset, int yOffset)
{
    Position newPos[NUM_CELLS];
    getCellPositions(b, newPos);
    for (int i = 0; i < NUM_CELLS; i++)
    {
        DrawRectangle(newPos[i].col * CELL_SIZE + xOffset, newPos[i].row * CELL_SIZE + yOffset, CELL_SIZE - 1, CELL_SIZE - 1, ghostBrickColors[b->blockType - 1]);
    }
}


void getCellPositions(const Block *b, Position out[NUM_CELLS])
{
    for (int i = 0; i < NUM_CELLS; i++)
    {
        Position tile = b->cells[b->rotateState][i];

        out[i].row = tile.row + b->rowOffset;
        out[i].col = tile.col + b->colOffset;
    }
}

int checkValidMove(const Block *b, const Direction dir, const Grid *g)
{
    Position newPos[4];
    getCellPositions(b, newPos);
    switch (dir)
    {
        case DOWN:
            for (int i = 0; i < 4; i++)
            {
                if (isCellOutside(newPos[i].row + 1, newPos[i].col) || !isCellEmpty(g, newPos[i].row + 1, newPos[i].col)) return 0;
            }    
            break;
        case LEFT:
            for (int i = 0; i < 4; i++)
            {
                if (isCellOutside(newPos[i].row, newPos[i].col - 1) || !isCellEmpty(g, newPos[i].row, newPos[i].col - 1)) return 0;
            }
            break;
        case RIGHT:
            for (int i = 0; i < 4; i++)
            {
                if (isCellOutside(newPos[i].row, newPos[i].col + 1) || !isCellEmpty(g, newPos[i].row, newPos[i].col + 1)) return 0;
            }
            break;
        default:
            for (int i = 0; i < 4; i++)
            {
                if(isCellOutside(newPos[i].row, newPos[i].col) || !isCellEmpty(g, newPos[i].row, newPos[i].col)) return 0;
            }
    }
    return 1;
}

int checkValidRotation(const Block *b, const Grid *g)
{
    Position newPos[4];
    for (int i = 0; i < NUM_CELLS; i++)
    {
        int newRotationState = b->rotateState < 3 ? b->rotateState + 1 : 0;
        Position tile = b->cells[newRotationState][i];

        newPos[i].row = tile.row + b->rowOffset;
        newPos[i].col = tile.col + b->colOffset;
    }
    for (int i = 0; i < 4; i++)
    {
        if (isCellOutside(newPos[i].row, newPos[i].col) || !isCellEmpty(g, newPos[i].row, newPos[i].col)) return 0;
    }
    return 1;
}

void lockBlock(const Block *b, Grid *g)
{
    Position newPos[4];
    getCellPositions(b, newPos);
    for (int i = 0; i < 4; i++)
    {
        setCellValue(g, newPos[i].row, newPos[i].col, b->blockType);
    }
}

void resetBlock(Block *b)
{
    b->rotateState = 0;
    switch (b->blockType)
    {
        case HERO:
            b->colOffset = 3;
            b->rowOffset = -1;
            break;
        case SMASHBOY:
            b->colOffset = 4;
            b->rowOffset = 0;
            break;
        default:
            b->colOffset = 3;
            b->rowOffset = 0;
            break;
    }
}