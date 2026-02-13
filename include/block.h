#ifndef BLOCK_H
#define BLOCK_H

#include "grid.h"

#define SWAP_BLOCK_PTR(a, b) do { Block *tmp = (a); (a) = (b); (b) = tmp; } while (0)

typedef struct Block Block;

typedef enum BLOCK_TYPE {
    ORANGE_RICKY = 1,
    BLUE_RICKY,
    HERO,
    SMASHBOY,
    RHODE_ISLAND_Z,
    TEEWEE,
    CLEVELAND_Z
} BLOCK_TYPE;

typedef enum Direction {
    DOWN = 1,
    RIGHT,
    LEFT
} Direction;

typedef struct Position
{
    int row, col;
} Position;

Block *createBlock(BLOCK_TYPE blockType);
Block *cloneBlock(const Block *src);
void destroyBlock(Block *b);
BLOCK_TYPE getBlockType(const Block *b);
int checkValidRotation(const Block *b, const Grid *g);
void rotate(Block *b);
void move(Block *b, Direction dir);
int hardDrop(Block *b, Grid *g);
int checkValidMove(const Block *b, const Direction dir, const Grid *g);
void lockBlock(const Block *b, Grid *g);
void drawBlock(const Block *b, int xOffset, int yOffset);
void drawGhostBlock(const Block *b, int xOffset, int yOffset);
void resetGhostBlockRow(Block *targetB, Block *fromB);
void resetBlock(Block *b);

#endif