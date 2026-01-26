#ifndef BLOCK_H
#define BLOCK_H

typedef struct Block Block;
typedef struct Cell
{
    int filled;
} Cell;


Block *createBlock();
void destroyBlock(Block *b);

#endif