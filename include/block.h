#ifndef BLOCK_H
#define BLOCK_H

#include "grid.h"

#define SWAP_BLOCK_PTR(a, b) do { Block *tmp = (a); (a) = (b); (b) = tmp; } while (0)

typedef struct Block Block;

typedef enum BLOCK_TYPE {
    ORANGE_RICKY = 1,
    BLUE_RICKY,
    CLEVELAND_Z,
    RHODE_ISLAND_Z,
    HERO,
    TEEWEE,
    SMASHBOY
} BLOCK_TYPE;

typedef enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
} Direction;

typedef struct Posistion
{
    int x, y;
} Posistion;

Block *createBlock(BLOCK_TYPE blockType);
void destroyBlock(Block *b);
BLOCK_TYPE getBlockType(Block *b);
void rotate(Block *b);
void move(Block *b, Direction dir);
int checkValidMove(Block *b, Direction dir, Grid *g);
void lockBlock(Block *b, Grid *g);

#endif